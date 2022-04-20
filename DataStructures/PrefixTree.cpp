#include <vector>
#include <memory>
#include <iostream>
#include <unordered_map>

class PrefixTree
{
    struct TrieNode
    {
        bool leaf = false;
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    };

public:
    PrefixTree() : root(std::make_unique<TrieNode>()) {}
    
    void insert(const std::string& word)
    {
        if (word.empty())
            return;

        TrieNode* iterator = root.get();
        for (size_t i = 0u; i < word.length(); ++i) {
            const auto it = iterator->children.find(word[i]);
            if (it == end(iterator->children)) {
                TrieNode* node = new TrieNode;
                iterator->children.emplace(word[i], node);
                iterator = node;
            } else {
                iterator = it->second.get();
            }
        }

        iterator->leaf = true;
    }

//                 l                l                                   l 
//       a.    c.    c.    u.    m.    u.    l.    a.    t.    o.    r.       
//   </> -> <> -> <> -> <> -> <> -> <> -> <> -> <> -> <> -> <> -> <> -> <> -> </>
//                                                                      n

    void erase(const std::string& word)
    {
        if (word.empty())
            return;


        std::function<void(TrieNode*, size_t)> remove_impl;
        remove_impl = [&remove_impl, &word] (TrieNode* node, size_t depth)
        {
            if (depth == word.size())
                node->leaf = false;

            const auto it = node->children.find(word[depth]);
            if (it != end(node->children)) {
                remove_impl(it->second.get(), depth + 1u);
                if (!it->second->leaf && it->second->children.empty())
                    node->children.erase(it);
            }
        };

        remove_impl(root.get(), 0u);
    }
    
    bool search(const std::string& word) const
    {
        TrieNode* key_node = find_key_node(word);
        return key_node && key_node->leaf;
    }
    
    bool starts_with(const std::string& prefix) const
    {
        return find_key_node(prefix);
    }

    std::vector<std::string> autocomplete(const std::string& prefix) const
    {
    	std::string word_path;
        TrieNode* iterator = root.get();
        for (size_t i = 0u; i < prefix.length(); ++i) {
            const auto it = iterator->children.find(prefix[i]);
            if (it == end(iterator->children)) {
                iterator = nullptr;
                break;
            }

            word_path += prefix[i];
            iterator = it->second.get();
        }

        if (!iterator)
        	return {};

    	std::vector<std::string> result;
    	std::function<void(TrieNode*)> impl;
    	impl = [&impl, &result, &word_path] (TrieNode* node)
    	{
    		for (const auto& it: node->children) {
    			word_path += it.first;
    			if (it.second->leaf)
    				result.push_back(word_path);

    			impl(it.second.get());
    			word_path.pop_back();
    		}
    	};

    	if (iterator->leaf)
    		result.push_back(word_path);

    	impl(iterator);
    	return result;
    }

private:
    TrieNode* find_key_node(const std::string& key) const
    {
    	if (key.empty())
    		return nullptr;

        TrieNode* iterator = root.get();
        for (size_t i = 0u; i < key.length(); ++i) {
            const auto it = iterator->children.find(key[i]);
            if (it == end(iterator->children))
                return nullptr;

            iterator = it->second.get();
        }

        return iterator;
    }

private:
    std::unique_ptr<TrieNode> root;
};

int main(int argc, char** argv)
{
	PrefixTree prefix_tree;
	prefix_tree.insert("accum");
	prefix_tree.insert("accumulator");
	prefix_tree.insert("ac");

	prefix_tree.insert("hello");
	prefix_tree.insert("world");

	{
		assert(!prefix_tree.search(""));
		assert(prefix_tree.search("accum"));
		assert(!prefix_tree.search("accu"));
		assert(prefix_tree.search("accumulator"));
		assert(!prefix_tree.search("accumulato"));
		assert(!prefix_tree.search("accumulators"));
		assert(prefix_tree.search("ac"));
	}
	{
		assert(!prefix_tree.starts_with(""));
		assert(prefix_tree.starts_with("h"));
		assert(prefix_tree.starts_with("he"));
		assert(prefix_tree.starts_with("hel"));
		assert(prefix_tree.starts_with("hell"));
		assert(prefix_tree.starts_with("hello"));
		assert(!prefix_tree.starts_with("hellou"));
		assert(!prefix_tree.starts_with("ellou"));
	}
    {
        assert(prefix_tree.autocomplete("a") == (std::vector<std::string>{ "ac", "accum", "accumulator" }));
        assert(prefix_tree.autocomplete("ac") == (std::vector<std::string>{ "ac", "accum", "accumulator" }));
        assert(prefix_tree.autocomplete("acc") == (std::vector<std::string>{ "accum", "accumulator" }));
        assert(prefix_tree.autocomplete("ax") == (std::vector<std::string>{}));
    }
    {
        prefix_tree.erase("accumulator");
        assert(!prefix_tree.search("accumulator"));
        assert(!prefix_tree.search("accumulato"));
        assert(!prefix_tree.search("accumulat"));
        assert(!prefix_tree.search("accumula"));
        assert(!prefix_tree.search("accumul"));
        assert(!prefix_tree.search("accumu"));
        assert(prefix_tree.search("accum"));

        prefix_tree.erase("accumul");
        prefix_tree.erase("accu");
        assert(prefix_tree.search("accum"));
        assert(prefix_tree.search("ac"));

        prefix_tree.erase("ac");
        assert(!prefix_tree.search("ac"));
        assert(prefix_tree.search("accum"));

        prefix_tree.erase("accum");
        assert(!prefix_tree.starts_with("a"));
    }

	return EXIT_SUCCESS;
}