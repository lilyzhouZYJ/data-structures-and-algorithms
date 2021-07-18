# Hash Table

## What is Hashing?

- A technique to perform insertions, deletions, and searches in constant average time.
- The ordering information among the elements is generally lost.
- **Hash table** - array of some fixed size, containing items
- Each **key** is mapped to some number using a **hash function**, which ideally ensures that two distinct keys get mapped to two distinct numbers.
  - When two keys are mapped to the same number, this is called a **collision**.

## Hash Functions

- Expectations for hash functions:
  - Reduces collisions
  - Distributes input keys across the hash table
  - Looks random

If input keys are integers:
- `Key mod TableSize` is generally a reasonable hash function when keys are integers.
  - Note: Need to choose `TableSize` with care, e.g.) If all `Key` values are multiples of 10, then `TableSize = 100` will not distribute the entries well.

If input keys are strings:
- Below are 3 hash functions that essentially follow the same logic: applying *multiplication (or bit shifting)* and *addition (or XOR)* to each byte of the string.

### **Hash Function I: computing a polynomial** (using Horner's rule)
$$\sum_{i=0}^{KeySize-1} Key [KeySize-i-1] \cdot 37^i$$
- Simple, reasonably fast.
- If the keys are too long, a common practice is not to use all the characters.

```c
/* 
 * 1) Hash Function by computing polynomial
 * Here we use 32 instead of 37 because we can replace it with <<5 to speed up the computation.
 * We can also replace addition with XOR to speed up the computation (see FNV functions below)
 */
uint64_t hash(unsigned char * str, int tableSize){
    uint64_t hashVal = 0;
    while(*str != '\0'){
        hashVal += (hashVal << 5) + *str; 
        str++;
    }
    hashVal %= tableSize;   // to fit hash value into the table
    return hashVal;
}
```

### **Hash Function II: FNV-1**

Fowler–Noll–Vo is a non-cryptographic hash function created by Glenn Fowler, Landon Curt Noll, and Kiem-Phong Vo.

For a 64-bit hash:
- The hash value will be a 64-bit unsigned integer.
- The **FNV offset basis** is the 64-bit value of 14695981039346656037 (or 0xcbf29ce484222325).
- The **FNV prime** is the 64-bit value of 1099511628211 (or 0x100000001b3).
- The multiplication returns the lower 64-bits of the product, and any overflow is discarded.
- The XOR is an 8-bit operation, since every `char` of the string is an 8-bit byte. The XOR only modifies the lower 8-bits of the hash value.

```c
#define FNV_PRIME ((1ULL<<40)+(1<<8)+0xb3)              // 1099511628211
#define FNV_OFFSET_BASIS (14695981039346656037ULL)

/* 2) Hash Function: FNV-1 */
uint64_t hashFNV1(unsigned char * str, int tableSize){
        uint64_t hashVal = FNV_OFFSET_BASIS;
        while(*str != '\0'){
                hashVal *= FNV_PRIME;           // multiplication first
                hashVal ^= *str;                // then XOR
                str++;
        }
        return hashVal % tableSize;
}
```

### **Hash Function III: FNV-1a**

FNV-1a differs from FNV-1 by swapping the order of XOR and multiplication.

```c
#define FNV_PRIME ((1ULL<<40)+(1<<8)+0xb3)              // 1099511628211
#define FNV_OFFSET_BASIS (14695981039346656037ULL)

/* 3) Hash Function: FNV-1a */
uint64_t hashFNV1a(unsigned char * str, int tableSize){
        uint64_t hashVal = FNV_OFFSET_BASIS;
        while(*str != '\0'){
                hashVal ^= *str;                // XOR first
                hashVal *= FNV_PRIME;           // then multiplication
                str++;
        }
        return hashVal % tableSize;
}
```

## Collision Resolution

Another important part of hashing is collision resolution, and there are several strategies for it.

### Separate Chaining

- Keep a list of all elements that hash to the same value -> We can use linked lists.
- Disadvantages:
  - Slow down the algorithm, due to the time required to allocate nodes.
- **Searches**:
  - Use the hash function to determine which list to traverse, then search the appropriate list.
- **Insertions**:
  - Use the hash function to determine which list to traverse, search through that list to ensure the key is not already present, and if the key turns out to be new, we insert it at the front of the list (out of convenience).
- **Deletions**:
  - Use the hash function to determine which list to traverse, search through that list to find the key, and remove the corresponding node.
- Important notes:
  - **Load factor $\lambda$**: $$\lambda = \frac{\text{Number of Entries in the Table}}{\text{Table Size}}$$
  - The average length of the linked lists is $\lambda$.
  - The effor required to perform a search is the constant time required to evaluate the hash function plus the time to traverse the list.
    - For an unsuccessful search, we need to traverse $\lambda$ nodes on average.
    - For a successful search, we need to traverse about $1 + (\frac{\lambda}{2})$ nodes.
      - Why? Note that the list contains the one node that stores the match plus zero or more other nodes. The expected number of "other nodes" in a table with $N$ elements and $M$ lists is $(N-1)/M = \lambda - 1/M$, and since $M$ is presumed to be large, this is essentially just $\lambda$. Half of the "other nodes" will be traversed on average, so combined with the matching node, we get an average search cost of $1 + (\frac{\lambda}{2})$ nodes.
      - This anaysis shows that the load factor is what really matters.
    - **The general rule for separate chaining: let $\lambda \approxeq 1$.**
  - Also a good idea to keep the table size prime to ensure good distribution.

### Open Addressing

- Try alternative cells until an empty cell is found.
  - Cells $h_0(x), h_1(x), h_2(x), ...$ are tried in succession, where $h_i(x) = (hash(x) + f(i)) \text{mod } TableSize$, with $f(0)=0$.
  - The function $f$ is the collision resolution strategy.
- **The load factor $\lambda$ is generally kept below $\lambda = 0.5$.**
- Such tables are called **probing hash tables**.

**1. Linear Probing**

- $f$ is a linear function of $i$: typically $f(i) = i$.
- Trying cells sequentially (with wraparound) until we find an empty cell.
- Could result in **primary clustering** - blocks of occupied cells, and keys that hases into the cluster will require several tries before collision is resolved, and then it will add to the cluster.
- The expected number of probes:
  - Insertions and unsuccessful searches: about $\frac{1}{2} (1 + 1/(1-\lambda)^2)$
  - Successful searches: about $\frac{1}{2} (1 + 1/(1-\lambda))$

**2. Quadratic Probing**

- Eliminates the primary clustering problem of linear probing.
- The collision function is quadratic: typically $f(i) = i^2$.
- **There is no guarantee of finding an empty cell once the table gets more than half full, or even before half full if the table size is not prime.**
  - Key theorem: *If quadratic probing is used, and the table size is prime, then a new element can always be inserted if the table is at least half empty.* (Theorem 5.1 in Mark Allen Weiss, *Data Structures and Algorithm Analysis*)
- Standard deletion cannot be performed --> **lazy deletion** is thus required.

**3. Double Hashing**

- Typically $f(i) = i \cdot hash_2(x)$.
  - Applying a second hash function and probe at a distance of $hash_2(x), 2 hash_2(x), ...$.
  - The second hash function need to be chosen with care: typically $hash_2(x) = R - (x \text{mod } R)$ works well, where $R$ is a prime smaller than table size.
- Disadvantage:
  - More costly, especially for keys like strings whose hash functions are expensive to compute

## Rehashing

When the table gets too full, operations will become too costly, and insertions could fail depending on the collision resolution strategy. A solution to this problem is to *rehash*.

- How to rehash:
  - Build a new larger table (usually about twice as big).
  - Scan down the entire original hash table, compute the new hash values for each, and insert them into the new table.
- When to rehash:
  - The usual strategy is to rehash when the table reaches a certain load factor.
- Disadvantages:
  - Very expensive - but acceptable as long as rehashing happens only infrequently.

## Other things to look into...

- Universal hashing
- Extendible hashing