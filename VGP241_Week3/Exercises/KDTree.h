#pragma once
#include <string>

struct Vector2
{
	int x = 0;
	int y = 0;
};

struct KDNode
{
	Vector2 data;
	KDNode* left = nullptr;
	KDNode* right = nullptr;
};

class KDTree
{
public:
	int RandomNumber(int min, int max)
	{
		return min + (rand() % (max - min));
	}

	// print tree
	void PrintDataAtHeightLevel(KDNode* node, int height, const std::string& side)
	{
		if (node == nullptr)
		{
			return;
		}

		if (height == 0)
		{
			std::cout << side << "(" << node->data.x << ", " << node->data.y << ") ";
		}
		else
		{
			PrintDataAtHeightLevel(node->left, height - 1, "L");
			PrintDataAtHeightLevel(node->right, height - 1, "R");

			if (height == 1)
			{
				std::cout << " ";
			}
		}
	}

	void PrintTree(KDNode* tree)
	{
		std::cout << "\n\n\nPrinting Tree:\n";

		for (int i = 0; i < 10; ++i)
		{
			PrintDataAtHeightLevel(tree, i, "ROOT");
			std::cout << "\n";
		}
	}

	// recursively deltes all nodes in the KD Tree
	void DeleteKDTree(KDNode* node)
	{
		if (node != nullptr)
		{
			DeleteKDTree(node->left);
			DeleteKDTree(node->right);

			delete node;
			node = nullptr;
		}
	}

	// dim is the level/current height we are at in the tree 
	// (starts at 0, goes to number of k elements, then repeats)
	KDNode* Insert(const Vector2& data, KDNode* prevNode, int dim)
	{
		if (prevNode == nullptr)
		{
			KDNode* node = new KDNode();
			node->data = data;
			return node;
		}

		if (prevNode->data.x == data.x && prevNode->data.y == data.y)
		{
			std::cout << "ERROR: Node has already been added!!!\n";
		}

		const int maxDim = 2; // (x, y)
		int nextDim = (dim + 1) % maxDim;

		// compare based on current dimension
		if (dim == 0) // since we are vector2, layer 0 compares the x value
		{
			// compare new data with prevNode data, only compare the x
			// if the new data.x is less than prevNode->data.x, data is inserted to the left
			if (data.x < prevNode->data.x)
			{
				prevNode->left = Insert(data, prevNode->left, nextDim);
			}
			else
			{
				prevNode->right = Insert(data, prevNode->right, nextDim);
			}
		}
		else if (dim == 1) // layer 1 compares the y value
		{
			if (data.y < prevNode->data.y)
			{
				prevNode->left = Insert(data, prevNode->left, nextDim);
			}
			else
			{
				prevNode->right = Insert(data, prevNode->right, nextDim);
			}
		}
		else
		{
			std::cout << "ERROR: Dimension is not set";
		}

		return prevNode;
	}

	Vector2 Minimum(const Vector2& a, const Vector2& b, const Vector2& c, int dim)
	{
		int aDimValue = (dim == 0) ? a.x : a.y;
		int bDimValue = (dim == 0) ? b.x : b.y;
		int cDimValue = (dim == 0) ? c.x : c.y;

		if (aDimValue < bDimValue && aDimValue < cDimValue)
		{
			return a;
		}

		if (bDimValue < aDimValue && bDimValue < cDimValue)
		{
			return b;
		}

		return c;
	}

	// Find Min (dim = dimension we`re looking for | cd = current dimension)
	Vector2 FindMin(KDNode* node, int dim, int cd)
	{
		if (node == nullptr)
		{
			Vector2 invalid;
			invalid.x = INT_MAX;
			invalid.y = INT_MAX;
			return invalid;
		}

		int nextCD = (cd + 1) % 2;

		if (cd == dim)
		{
			if (node->left == nullptr)
			{
				return node->data;
			}

			return FindMin(node->left, dim, nextCD);
		}

		// check the left and right branch and the current node is smallest
		return Minimum(FindMin(node->left, dim, nextCD), FindMin(node->right, dim, nextCD), node->data, dim);
	}

	// Delete node
	KDNode* Delete(const Vector2& data, KDNode* node, int dim)
	{
		if (node == nullptr)
		{
			std::cout << "ERROR: Node was not found with (" << data.x << ", " << data.y << ")\n";
			return node;
		}

		int nextDim = (dim + 1) % 2;

		// we found the node
		if (data.x == node->data.x && data.y == node->data.y)
		{
			if (node->right != nullptr)
			{
				// find smallest, stomp over data
				node->data = FindMin(node->right, dim, nextDim);

				// delete the data that is now a copy
				node->right = Delete(node->data, node->right, nextDim);
			}
			// we do not have right sub tree (no right subtree solution)
			else if (node->left != nullptr)
			{
				// get smallest, in left, stomp over
				node->data = FindMin(node->left, dim, nextDim);

				// swapping right branch with left branch since there is not right branch
				node->right = Delete(node->data, node->left, nextDim);
			}
			// no subtrees, so super easy
			else
			{
				delete node;
				node = nullptr;
			}
		}
		// we did not find the node
		else
		{
			if (dim == 0) // looking at the x dimension
			{
				if (data.x < node->data.x)
				{
					node->left = Delete(data, node->left, nextDim);
				}
				else
				{
					node->right = Delete(data, node->right, nextDim);
				}
			}
			else // we are looking in the y dimension
			{
				if (data.y < node->data.y)
				{
					node->left = Delete(data, node->left, nextDim);
				}
				else
				{
					node->right = Delete(data, node->right, nextDim);
				}
			}
		}

		return node;
	}

	// Find Range
	int gIterationCount = 0;
	void PrintRange(const Vector2& minRange, const Vector2& maxRange, KDNode* node, int dim)
	{
		if (node == nullptr)
			return;

		++gIterationCount;

		// if the value is within the min/max range, print
		if (node->data.x >= minRange.x && node->data.x <= maxRange.x && node->data.y >= minRange.y && 
			node->data.y <= maxRange.y)
		{
			std::cout << "(" << node->data.x << ", " << node->data.y << ")\n";
		}

		int nextDim = (dim + 1) % 2;
		
		if (dim == 0) // looking at x
		{
			// if min x is still smaller than current x, continue left
			if (minRange.x <= node->data.x)
			{
				PrintRange(minRange, maxRange, node->left, nextDim);
			}

			// if max x is still larger than current x, continue right
			if (node->data.x <= maxRange.x)
			{
				PrintRange(minRange, maxRange, node->right, nextDim);
			}
		}
		else //looking at y
		{
			if (minRange.y <= node->data.y)
			{
				PrintRange(minRange, maxRange, node->left, nextDim);
			}

			if (node->data.y <= maxRange.y)
			{
				PrintRange(minRange, maxRange, node->right, nextDim);
			}
		}
	}

	int DistanceSquared(const Vector2& a, const Vector2& b)
	{
		Vector2 diff;

		diff.x = a.x - b.x;
		diff.y = a.y - b.y;

		return (diff.x * diff.x) + (diff.y * diff.y);
	}

	KDNode* Closest(KDNode* a, KDNode* b, const Vector2& v)
	{
		if (a == nullptr)
			return b;

		if (b == nullptr)
			return a;

		int aD = DistanceSquared(a->data, v);
		int bD = DistanceSquared(b->data, v);

		if (aD < bD)
			return a;

		return b;
	}

	// Find the node closest to the point
	KDNode* NearestNeighbor(const Vector2& v, KDNode* node, int dim)
	{
		if (node == nullptr)
			return nullptr;

		KDNode* nextBranch = nullptr;
		KDNode* otherBranch = nullptr;

		int nextDim = (dim + 1) % 2;

		if (dim == 0) // on x dimension
		{
			if (v.x < node->data.x)
			{
				nextBranch = node->left;
				otherBranch = node->right;
			}
			else
			{
				nextBranch = node->right;
				otherBranch = node->left;
			}
		}
		else // compare y
		{
			if (v.y < node->data.y)
			{
				nextBranch = node->left;
				otherBranch = node->right;
			}
			else
			{
				nextBranch = node->right;
				otherBranch = node->left;
			}
		}

		KDNode* temp = NearestNeighbor(v, nextBranch, nextDim);
		KDNode* best = Closest(temp, node, v);

		float distSqr = DistanceSquared(best->data, v);
		float planeDist = 0.0f;

		if (dim == 0)
		{
			planeDist = v.x - node->data.x;
		}
		else
		{
			planeDist = v.y - node->data.y;
		}

		if (distSqr >= planeDist * planeDist)
		{
			temp = NearestNeighbor(v, otherBranch, nextDim);
			best = Closest(temp, best, v);
		}

		return best;
	}

	void Exercise2KDTree()
	{
		int maxNumbers = 20;
		int min = 1;
		int max = 100;
		KDNode* root = nullptr;
		Vector2 deleteDataVal;
		Vector2 data;

		for (int i = 0; i < maxNumbers; ++i)
		{
			data.x = RandomNumber(min, max);
			data.y = RandomNumber(min, max);

			KDNode* newNode = Insert(data, root, 0);

			if (root == nullptr)
			{
				root = newNode;
			}

			std::cout << "(" << data.x << ", " << data.y << ") ";

			if (i == maxNumbers / 2)
			{
				deleteDataVal = data;
			}
		}

		std::cout << "\n\n\n";
		PrintTree(root);

		// Find the min x and y
		// FindMin (treeRoot, dimension we want, dimension are we currently in)
		Vector2 minX = FindMin(root, 0, 0);
		Vector2 minY = FindMin(root, 1, 0);

		std::cout << "MinX: (" << minX.x << ", " << minX.y << ")\n";
		std::cout << "MinY: (" << minY.x << ", " << minY.y << ")\n";
		std::cout << "\n\n\n";

		// delete some value and reprint
		std::cout << "Deleting Data (" << deleteDataVal.x << ", " << deleteDataVal.y << "):\n";
		root = Delete(deleteDataVal, root, 0);
		PrintTree(root);

		std::cout << "\n\n\n";

		std::cout << "Print within range:\n";

		Vector2 minRange = { 20, 20 };
		Vector2 maxRange = { 80, 80 };

		gIterationCount = 0;

		PrintRange(minRange, maxRange, root, 0);

		std::cout << "\nNumIterations: " << gIterationCount << "\n";

		Vector2 target;

		std::cout << "\n\nNearest Neighbor\n";
		std::cout << "Enter X: ";
		std::cin >> target.x;

		std::cout << "Enter Y: ";
		std::cin >> target.y;

		KDNode* nearestNeighbor = NearestNeighbor(target, root, 0);

		std::cout << "Closest Point (" << nearestNeighbor->data.x << ", " << nearestNeighbor->data.y << ")\n";

		DeleteKDTree(root);
	}
};