#include <iostream>
#include <memory>
#include <utility>

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
class bst 
{
private:
    struct Node 
    {
        std::pair<const Key, T> value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;

        Node(const std::pair<const Key, T>& value)
            : value(value), left(nullptr), right(nullptr), parent() {}
    };

public:
    class iterator 
    {
    private:
        std::shared_ptr<Node> current;
        std::weak_ptr<Node> root;

    public:
        iterator(std::shared_ptr<Node> current, std::weak_ptr<Node> root)
            : current(current), root(root) {}

        std::pair<const Key, T>& operator*() const 
        {
            return current->value;
        }

        iterator& operator++() 
        {
            if (current->right) 
            {
                current = current->right;
                while (current->left) 
                {
                    current = current->left;
                }
            } 
            else 
            {
                std::shared_ptr<Node> p = nullptr;
                while (!current->parent.expired() && current == p->right) 
                {
                    p = current;
                    current = p->parent.lock();
                }
                current = p;
            }

            return *this;
        }

        iterator operator++(int) 
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const 
        {
            return current == other.current && root.lock() == other.root.lock();
        }

        bool operator!=(const iterator& other) const 
        {
            return !(*this == other);
        }
    };

    bst() : root(nullptr), size_(0) {}

    ~bst() 
    {
        clear();
    }

    T& operator[](const Key& key) 
    {
        std::shared_ptr<Node> node = findNode(key);

        if (!node) 
        {
            node = insertNode(std::make_pair(key, T()));
        }

        return node->value.second;
    }

    T& at(const Key& key) 
    {
        std::shared_ptr<Node> node = findNode(key);

        if (!node) 
        {
            throw std::out_of_range("Key not found");
        }

        return node->value.second;
    }

    std::pair<iterator, bool> insert(const std::pair<const Key, T>& value) 
    {
        std::shared_ptr<Node> node = findNode(value.first);

        if (!node) 
        {
            node = insertNode(value);
            return std::make_pair(iterator(node, root), true);
        }

        return std::make_pair(iterator(node, root), false);
    }

    void erase(const Key& key) 
    {
        std::shared_ptr<Node> node = findNode(key);

        if (!node) 
        {
            return;
        }

        eraseNode(node);
    }

    iterator find(const Key& key) 
    {
        std::shared_ptr<Node> node = findNode(key);

        if (!node) 
        {
            return end();
        }

        return iterator(node, root);
    }

    bool contains(const Key& key) 
    {
        return findNode(key) != nullptr;
    }

    bool empty() const 
    {
        return size_ == 0;
    }

    size_t size() const 
    {
        return size_;
    }

    void clear() 
    {
        eraseSubtree(root);
        size_ = 0;
    }

    iterator begin() const 
    {
        std::shared_ptr<Node> current = root;
        while (current && current->left) 
        {
            current = current->left;
        }
        return iterator(current, root);
    }

    iterator rbegin() const 
    {
        std::shared_ptr<Node> current = root;
        while (current && current->right) 
        {
            current = current->right;
        }
        return iterator(current, root);
    }

    iterator end() const 
    {
        return iterator(nullptr, root);
    }

    iterator rend() const 
    {
        return iterator(nullptr, root);
    }

private:
    std::shared_ptr<Node> root;
    size_t size_;

    std::shared_ptr<Node> findNode(const Key& key) const 
    {
        std::shared_ptr<Node> current = root;
        while (current) 
        {
            if (Compare()(key, current->value.first)) 
            {
                current = current->left;
            } else if (Compare()(current->value.first, key)) 
            {
                current = current->right;
            } 
            else 
            {
                return current;
            }
        }
        return nullptr;
    }

    std::shared_ptr<Node> insertNode(const std::pair<const Key, T>& value) 
    {
        std::shared_ptr newNode = std::make_shared(value);

        if (root == nullptr) 
        {
            root = newNode;
        } 
        else 
        {
            std::shared_ptr<Node> current = root;
            std::shared_ptr<Node> parent;

            while (current) 
            {
                parent = current;

                if (Compare()(newNode->value.first, current->value.first)) 
                {
                    current = current->left;
                } 
                else 
                {
                    current = current->right;
                }
            }

            newNode->parent = parent;

            if (Compare()(newNode->value.first, parent->value.first)) 
            {
                parent->left = newNode;
            } 
            else 
            {
                parent->right = newNode;
            }
        }

        size_++;
        return newNode;
    }

    void eraseNode(std::shared_ptr<Node> node) 
    {
        if (node->left && node->right) 
        {
            std::shared_ptr<Node> successor = findMinNode(node->right);
            node->value = successor->value;
            eraseNode(successor);
        } 
        else if (node->left) 
        {
            replaceNode(node, node->left);
        } 
        else if (node->right) 
        {
            replaceNode(node, node->right);
        } 
        else 
        {
            replaceNode(node, nullptr);
        }
    }

    std::shared_ptr<Node> findMinNode(std::shared_ptr<Node> start) const 
    {
        std::shared_ptr<Node> current = start;

        while (current && current->left) 
        {
            current = current->left;
        }

        return current;
    }

    void replaceNode(std::shared_ptr<Node> node, std::shared_ptr<Node> replacement) 
    {
        std::shared_ptr<Node> parent = node->parent.lock();

        if (parent) 
        {
            if (node == parent->left) 
            {
                parent->left = replacement;
            } 
            else 
            {
                parent->right = replacement;
            }
        } 
        else 
        {
            root = replacement;
        }

        if (replacement) 
        {
            replacement->parent = parent;
        }

        size_--;
    }

    void eraseSubtree(std::shared_ptr<Node> node) 
    {
        if (node) 
        {
            eraseSubtree(node->left);
            eraseSubtree(node->right);
            node.reset();
        }
    }
};

int main() 
{

    return 0;
}