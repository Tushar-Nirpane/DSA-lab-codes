# DSA Lab Codes

A collection of Data Structures and Algorithms lab programs written in C. Each
program is a standalone, menu-driven console application that demonstrates one
core data structure or algorithm on a small real-world scenario.

All programs compile cleanly with `-Wall -Wextra` under C11.

## Programs

| # | File | Data Structure / Algorithm | Scenario |
|---|------|----------------------------|----------|
| 1 | `p1_array_operations.c` | Array, linear search, binary search, bubble sort | Student marks record |
| 2 | `p2_bubble_sort.c` | Bubble sort (optimized, early exit) | Sorting student roll numbers |
| 3 | `p3_contact_list.c` | Singly linked list | Phone contact list |
| 4 | `p4_browser_navigation.c` | Two stacks (back / forward) | Browser history navigation |
| 5 | `p5_patient_queue.c` | Circular queue (array based) | Hospital patient waiting line |
| 6 | `p6_bst.c` | Binary search tree | Student roll number index |
| 7 | `p7_graph_social.c` | Graph (adjacency matrix), BFS, DFS | Social network connections |
| 8 | `p8_hash_table.c` | Hash table with linear probing | Library book lookup |

### 1. Array Operations (`p1_array_operations.c`)

Stores up to 100 integer marks in a fixed-size array. Supports insertion at the
end, deletion at a given position (with element shifting), display, linear
search, and a sort-then-binary-search option.

- `linearSearch` — O(n)
- `binarySearch` — O(log n), requires a sorted array
- `sortArray` — bubble sort, O(n²)

### 2. Bubble Sort (`p2_bubble_sort.c`)

Reads *n* roll numbers and sorts them with bubble sort. After every pass the
current array state is printed so the sorting process can be traced. The
`swapped` flag terminates the sort early when the array is already ordered,
giving O(n) best-case behaviour.

- Time — O(n²) average and worst case, O(n) best case
- Space — O(1), in place

### 3. Contact List (`p3_contact_list.c`)

A singly linked list of contacts (name + phone). Supports insertion at the
beginning and at the end, deletion by name, search by name, display, and frees
all nodes on exit.

- Insert at beginning — O(1)
- Insert at end — O(n)
- Delete / search by name — O(n)

### 4. Browser Navigation (`p4_browser_navigation.c`)

Simulates browser history with two stacks: a *back* stack and a *forward*
stack. Visiting a new page pushes the current page onto the back stack and
clears the forward stack, matching real browser behaviour.

- `visit`, `goBack`, `goForward` — each O(1)

### 5. Patient Queue (`p5_patient_queue.c`)

A circular queue of patients holding a patient ID and an arrival time. Because
the queue wraps around the array, freed slots at the front are reused instead
of being wasted.

- `addPatient` (enqueue), `attendPatient` (dequeue) — O(1)
- `viewPatients` — O(n)

### 6. Binary Search Tree (`p6_bst.c`)

A BST keyed on student roll numbers. Supports insertion, deletion (covering the
leaf, single-child and two-children cases with the in-order successor),
iterative search, and in-order / pre-order / post-order traversals. Duplicate
roll numbers are rejected.

- Insert, delete, search — O(h), where h is the tree height
- In-order traversal yields roll numbers in ascending order

### 7. Social Graph (`p7_graph_social.c`)

An undirected graph of up to 50 users stored as an adjacency matrix. Users are
created on first mention, connections are added symmetrically, and both BFS and
DFS traversals are provided.

- Edge insert — O(1)
- BFS / DFS — O(V²) with a matrix representation

### 8. Hash Table (`p8_hash_table.c`)

A hash table of 11 slots storing library book IDs, using the division hash
`key % 11` with linear probing for collision resolution. The number of probes
per insertion is reported, and search stops as soon as an empty slot is
reached.

- Insert / search — O(1) average, O(n) worst case

## Building and Running

Each program is self-contained. Compile any one of them on its own:

```bash
cc -std=c11 -Wall -Wextra p1_array_operations.c -o p1
./p1
```

Or compile all of them at once:

```bash
for f in p*.c; do cc -std=c11 -Wall -Wextra "$f" -o "${f%.c}"; done
```

## Notes

- Every program is menu driven and loops until `0` is entered.
- Input is validated: out-of-range positions, duplicate keys, queue/stack
  overflow and non-numeric input are all handled.
- All heap memory (linked list nodes, tree nodes) is released before exit.

## License

MIT — see [LICENSE](LICENSE).

---

## 👥 Contributors

| Contributor | Role |
| :--- | :--- |
| [**Tushar Nirpane**](https://github.com/Tushar-Nirpane) | Author & maintainer |
