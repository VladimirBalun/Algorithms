#include <iostream>

template<typename T>
class BinarySearchTree 
{
public:
	explicit BinarySearchTree() : size(0) {}
	explicit BinarySearchTree(const BinarySearchTree& other);
	explicit BinarySearchTree(BinarySearchTree&& other);
	BinarySearchTree& operator = (const BinarySearchTree& other);

	void add(const T& value);
	void remove(const T& value);
	void clear();

	size_t getSize() const;
	size_t getDepth() const;

	bool isConatains(const T& value) const;
	bool isEmpty() const;

	~BinarySearchTree();
private:
	struct Node
	{
		T value;
		Node* leftChild;
		Node* rightChild;
	};

	// recursive
	void removeNode(Node* node);
	void addNode(Node* node, const T& value);
	Node* copyNode(Node* node);
	Node* findNodeWithParent(const T& value, Node*& parent) const;
	size_t findMaxDepth(Node* node) const;

	Node* root;
	size_t size;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other)
{
	root = copyNode(other.root);
	size = other.size;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree&& other)
{
	root = other.root;
	size = other.size;
	other.root = nullptr;
	other.size = 0;
}

template<typename T>
auto BinarySearchTree<T>::copyNode(Node* node) -> Node*
{
	if (node == nullptr)
	{
		return nullptr;
	}

	Node* newNode = new Node();
	newNode->value = node->value;
	newNode->leftChild = copyNode(node->leftChild);
	newNode->rightChild = copyNode(node->rightChild);
	return newNode;
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator = (const BinarySearchTree& other)
{
	if (!isEmpty()) 
	{
		clear();
	}

	root = copyNode(other.root);
	size = other.size;
	return *this;
}

template<typename T>
bool BinarySearchTree<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
void BinarySearchTree<T>::add(const T& value)
{
	if (isEmpty()) 
	{
		root = new Node;
		root->value = value;
		root->leftChild = nullptr;
		root->rightChild = nullptr;
	}
	else 
	{
		addNode(root, value);
	}
	size++;
}

template<typename T>
void BinarySearchTree<T>::addNode(Node* node, const T& value)
{
	if (value < node->value) 
	{
		if (node->leftChild == nullptr) 
		{
			node->leftChild = new Node;
			node = node->leftChild;
			node->value = value;
			node->leftChild = nullptr;
			node->rightChild = nullptr;
		}
		else
		{
			addNode(node->leftChild, value);
		}
	}
	else
	{
		if (node->rightChild == nullptr)
		{
			node->rightChild = new Node;
			node = node->rightChild;
			node->value = value;
			node->leftChild = nullptr;
			node->rightChild = nullptr;
		}
		else
		{
			addNode(node->rightChild, value);
		}
	}
}

template<typename T>
bool BinarySearchTree<T>::isConatains(const T& value) const
{
	if (isEmpty())
	{
		return false;
	}

	Node* parent;
	return findNodeWithParent(value, parent) != nullptr;
}

template<typename T>
auto BinarySearchTree<T>::findNodeWithParent(const T& value, Node*& parent) const -> Node*
{
	Node* tmpPtr = root;
	parent = nullptr;
	while (tmpPtr != nullptr)
	{
		if (value < tmpPtr->value)
		{
			parent = tmpPtr;
			tmpPtr = tmpPtr->leftChild;
		}
		else if (value > tmpPtr->value)
		{
			parent = tmpPtr;
			tmpPtr = tmpPtr->rightChild;
		}
		else
		{
			break;
		}
	}
	return tmpPtr;
}

template<typename T>
void BinarySearchTree<T>::remove(const T& value)
{
	if (isEmpty()) 
	{
		return;
	}

	Node* parent;
	Node* delNode = findNodeWithParent(value, parent);
	if (delNode == nullptr) 
	{
		return;
	}

	if (delNode->rightChild == nullptr) 
	{
		if (delNode->value < parent->value) 
		{
			parent->leftChild = delNode->leftChild;
		}
		else 
		{
			parent->rightChild = delNode->leftChild;
		}
		delete delNode;
	}
	else 
	{
		Node* leftMost = delNode->rightChild;
		while (leftMost->leftChild != nullptr) 
		{
			leftMost = leftMost->leftChild;
		}
		std::swap(delNode->value, leftMost->value);
		delete leftMost;
	}
	size--;
}

template<typename T>
void BinarySearchTree<T>::clear()
{
	if (!isEmpty()) 
	{
		removeNode(root);
		size = 0;
	}
}

template<typename T>
void BinarySearchTree<T>::removeNode(Node* node)
{
	if (node != nullptr)
	{
		removeNode(node->leftChild);
		removeNode(node->rightChild);
		delete node;
	}
}

template<typename T>
size_t BinarySearchTree<T>::getSize() const
{
	return size;
}

template<typename T>
size_t BinarySearchTree<T>::getDepth() const
{
	if (isEmpty()) 
	{
		return 0;
	}

	return findMaxDepth(root);
}

template<typename T>
size_t BinarySearchTree<T>::findMaxDepth(Node* node) const
{
	if (node == nullptr) 
	{
		return 0;
	}
	else 
	{
		size_t lMaxDepth = findMaxDepth(node->leftChild);
		size_t rMaxDepth = findMaxDepth(node->rightChild);
		if (lMaxDepth > rMaxDepth) 
		{
			return (lMaxDepth + 1);
		}
		else 
		{
			return (rMaxDepth + 1);
		}
	}
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	clear();
}

int main()
{
	BinarySearchTree<int> tree;
	tree.add(5);
	tree.add(4);
	tree.add(6);

	BinarySearchTree<int> tree2(tree);
	tree2.add(12);
	tree2.add(2);
	tree2.add(3);

	tree.clear();
	std::cout << "Size: " << tree2.getSize() << " Depth: " << tree2.getDepth() << std::endl;
	tree2.remove(3);
	std::cout << "Size: " << tree2.getSize() << " Depth: " << tree2.getDepth() << std::endl;

	return EXIT_SUCCESS;
}