# Sparse Array Using a Trie

This project implements a **sparse array** using a **trie data structure** instead of a hash table.

Hash tables are commonly used to store values indexed by sparse keys from a universe \(N\). However, in the worst case their access time may degrade significantly. A trie-based approach provides a **better pessimistic time bound**, which makes it a good alternative for this task.

---

# Trie Structure

The trie is defined by two parameters:

- **n** – number of children of the root node
- **k** – number of children for every other node

Structure:

- The **root node has `n` children**
- Every other node has **`k` children**
- Each node can store **at most one key**

---

# Insertion

To insert a key `x`:

1. Start at the **root**.
2. If the root is empty, store the key there.
3. Otherwise:
   - Compute `div = x mod n`
   - Move to the corresponding child node.
4. If that node is occupied:
   - Compute `div = div mod k`
   - Move to the next child.
5. Repeat until a **free node** is found.

If the key already exists, the program prints:

```
x exist
```

Otherwise, nothing is printed.

---

# Lookup

Searching is performed in the same way as insertion:

1. Start from the root.
2. Follow child nodes determined by:
   - `x mod n`
   - repeated `mod k`
3. Stop when:
   - the key `x` is found, or
   - an empty node is reached.

Output:

```
x exist
```

or

```
x not exist
```

---

# Deletion

To delete a key `x`, the node `p` containing the key must first be found.

Cases:

### Leaf node
If `p` has **no children**, it is deleted directly.

### Internal node
If `p` has children:

1. Find a **candidate node `q`**
2. `q` must be a **leaf node**
3. The algorithm always selects the **leftmost leaf**
4. Copy the key from `q` to `p`
5. Delete node `q`

If the key does not exist, the program prints:

```
x not exist
```

Otherwise nothing is printed.

---

# Supported Commands

| Command | Description |
|------|------|
| `I x` | Insert key `x` |
| `L x` | Lookup key `x` |
| `D x` | Delete key `x` |
| `P` | Print the contents of the trie in **preorder traversal** |

**Important:**  
During deletion the **leftmost external node must be chosen**. Otherwise the tree structure will differ, which affects the preorder output.

---

# Input Format

```
m
min max
n k

<commands>
```

Where:

- `m` – number of commands
- `min max` – range of possible input values
- `n k` – parameters of the trie
- followed by `m` commands

---

# Output Format

Each line contains the result of a command if output is required.

Commands that may produce output:

- `I x`
- `L x`
- `D x`
- `P`

If an operation succeeds and does not require output (e.g., successful insertion), **no line is printed**.

---

# Example

## Input

```
29
0 511
8 4

I 3
I 31
I 150
I 190
I 130
I 174
I 81
I 30
I 203
P
L 32
L 30
L 150
D 150
L 150
I 150
L 150
D 3
L 3
I 3
L 3
D 3
L 3
D 30
L 30
I 30
L 30
D 30
L 30
```

## Output

```
3 81 130 203 150 174 190 30 31
32 not exist
30 exist
150 exist
150 not exist
150 exist
3 not exist
3 exist
3 not exist
30 not exist
30 exist
30 not exist
```
