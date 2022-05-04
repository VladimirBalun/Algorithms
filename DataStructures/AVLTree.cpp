#include <cassert>
#include <functional>

class AVLTree
{
    struct TreeNode
    {
        TreeNode* left;
        TreeNode* right;
        int key = 0;
        int8_t height = 1;

        explicit TreeNode(int k)
            : key(k) {}
    };

public:
    void insert(int key)
    {
        std::function<TreeNode*(TreeNode*)> impl;
        impl = [this, &impl, key] (TreeNode* node)
        {
            if (!node)
                return new TreeNode(key);

            if (node->key > key)
                node->left = impl(node->left);
            else
                node->right = impl(node->right);

            return balance(node);
        };

        m_root = impl(m_root);
    }

    TreeNode* find(int key) const
    {
        std::function<TreeNode*(TreeNode*)> impl;
        impl = [&impl, key] (TreeNode* node) -> TreeNode*
        {
            if (!node)
                return nullptr;

            if (node->key < key)
                return impl(node->right);
            else if (node->key > key)
                return impl(node->left);
            else
                return node;
        };

        return impl(m_root);
    };

    void remove(int key)
    {
        std::function<TreeNode*(TreeNode*, int)> impl;
        impl = [&impl, this] (TreeNode* node, int key) -> TreeNode*
        {
            if (!node)
                return nullptr;

            if (key < node->key) {
                node->left = impl(node->left, key);
                return node;
            } else if (key > node->key) {
                node->right = impl(node->right, key);
                return node;
            } else {
                TreeNode* root = join(node->left, node->right);
                delete node;
                return root;
            }
        };

        m_root = impl(m_root, key);
    }

    ~AVLTree()
    {
        std::function<void(TreeNode*)> impl;
        impl = [&impl] (TreeNode* node)
        {
            if (node->left)
                impl(node->left);
            if (node->right)
                impl(node->right);

            delete node;
        };

        if (m_root)
            impl(m_root);
    }

private:
    int8_t height(TreeNode* node) const
    {
        return node ? node->height : 0;
    }

    int8_t balance_factor(TreeNode* node) const
    {
        return height(node->right) - height(node->left);
    }

    void fix_height(TreeNode* node)
    {
        const int8_t height_left = height(node->left);
        const int8_t height_right = height(node->right);
        node->height = (height_left > height_right ? height_left : height_right) + 1;
    }

    TreeNode* rotate_right(TreeNode* node)
    {
        TreeNode* new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;

        fix_height(node);
        fix_height(new_node);
        return new_node;
    }

    TreeNode* rotate_left(TreeNode* node)
    {
        TreeNode* new_node = node->right;
        node->right = new_node->left;
        new_node->left = node;

        fix_height(node);
        fix_height(new_node);
        return new_node;
    }

    TreeNode* balance(TreeNode* node)
    {
        fix_height(node);

        if (balance_factor(node) == 2) {
            if (balance_factor(node->right) < 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        if (balance_factor(node) == -2) {
            if (balance_factor(node->left) > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        return node;
    }

    TreeNode* join(TreeNode* left, TreeNode* right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        left->right = join(left->right, right);
        fix_height(left);
        return left;
    }


private:
    TreeNode* m_root;
};

int main(int argc, char** argv)
{
    AVLTree tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(15);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    tree.insert(35);
    tree.insert(40);

    {
        assert(tree.find(5));
        assert(!tree.find(6));
        assert(tree.find(10));
        assert(!tree.find(11));
        assert(tree.find(15));
        assert(!tree.find(16));
        assert(tree.find(20));
        assert(!tree.find(21));
        assert(tree.find(25));
        assert(!tree.find(26));
        assert(tree.find(30));
        assert(!tree.find(31));
        assert(tree.find(35));
        assert(!tree.find(36));
        assert(tree.find(40));
        assert(!tree.find(41));
    }

    tree.remove(20);
    tree.remove(25);
    tree.remove(30);

    {
        assert(tree.find(5));
        assert(!tree.find(6));
        assert(tree.find(10));
        assert(!tree.find(11));
        assert(tree.find(15));
        assert(!tree.find(16));
        assert(!tree.find(20));
        assert(!tree.find(21));
        assert(!tree.find(25));
        assert(!tree.find(26));
        assert(!tree.find(30));
        assert(!tree.find(31));
        assert(tree.find(35));
        assert(!tree.find(36));
        assert(tree.find(40));
        assert(!tree.find(41));
    }

    return EXIT_SUCCESS;
}
