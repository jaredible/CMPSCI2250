# Iterating through all possible character combinations of string for all lengths <= K

This code block will iterate through all possible character combinations of a string for all lengths <= K.
chars is a string and binaryTree is just an ordinary binary tree.

```c++
int length = chars.length();
string s; // Node value buffer
for (unsigned int l = 0; l < K; l++) {
	for (unsigned int i = 0; i < length - l; i++) {
		for (unsigned int j = i; j <= i + l; j++)
			s += chars[j]; // Append char onto buffer
		binaryTree.insertNode(s); // Insert the string as a node
		s = ""; // Clear buffer
	}
}
```

Loops K times and is used as a length.

```c++
for (unsigned int l = 0; l < K; l++)
```

Loops (lengths - l) times and sets starting index for upcoming substrings of chars string.

```c++
for (unsigned int i = 0; i < length - l; i++)
```

Loops a total of (i + l + 1) times at starting index i of chars string.

```c++
for (unsigned int j = i; j <= i + l; j++)
```

##TODO Use gifs to visualize
