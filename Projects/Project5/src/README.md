# Testing
Testing

```c++
for (unsigned int l = 0; l < K; l++) {
		for (unsigned int i = 0; i < length - l; i++) {
			for (unsigned int j = i; j <= i + l; j++)
				s += chars[j]; // Append char onto buffer
			binaryTree.insertNode(s); // Insert the string as a node
			s = ""; // Clear buffer
		}
	}
```