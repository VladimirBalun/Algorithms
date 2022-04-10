#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <initializer_list>

class InvertedIndex
{
public:
	explicit InvertedIndex(std::initializer_list<std::pair<std::string, std::string>> documents)
	{
		for (auto& document: documents)
			add_document(std::move(document.first), std::move(document.second));
	}

	void add_document(std::string name, std::string text)
	{
		for (auto& word: extract_words_from_text(text))
			m_inverted_index[std::move(word)].insert(name);
			
		m_documents.emplace_back(std::move(name), std::move(text));
	}

	std::vector<std::string> find_documents_by_text(std::string_view text) const
	{
		std::vector<const std::unordered_set<std::string>*> documents;
		for (const auto& word: extract_words_from_text(text)) {
			auto it = m_inverted_index.find(word);
			if (it != end(m_inverted_index)) {
				documents.push_back(&it->second);
			}
		}

		return find_documents_inersection(documents);
	}

private:
	std::string construct_word(std::string_view text, ssize_t word_begin, ssize_t word_end) const
	{
		std::string word;
		assert(word_begin != word_end);
		word.reserve(word_end - word_begin + 2u);
		for (size_t i = word_begin + 1; i < word_end + 1; ++i) {
			word += std::tolower(text[i]);
		}

		return word;
	}

	std::vector<std::string> extract_words_from_text(std::string_view text) const
	{
		ssize_t word_begin = -1;
		ssize_t word_end = -1;
		std::vector<std::string> words;

		for (size_t i = 0u; i < text.size(); ++i) {
			if (!std::isalpha(text[i])) {
				if (word_begin != word_end)
					words.push_back(construct_word(text, word_begin, word_end));
				word_begin = word_end = i;
			} else {
				++word_end;
			}
		}

		if (word_begin != word_end)
			words.push_back(construct_word(text, word_begin, word_end));

		return words;
	}

	std::vector<std::string> find_documents_inersection(const std::vector<const std::unordered_set<std::string>*>& documents) const
	{
		if (documents.empty())
			return std::vector<std::string>{};
		
		if (documents.size() == 1u)
			std::vector<std::string>(begin(*documents.front()), end(*documents.front()));
		
		auto documents_intersection = *documents.front();
		for (auto it = begin(documents_intersection); it != end(documents_intersection);) {
			bool need_to_increment = true;
			for (size_t i = 1u; i < documents.size(); ++i) {
				if (documents[i]->count(*it) == 0u) {
					documents_intersection.erase(it++);
					need_to_increment = false;
					break;
				}
			}

			if (need_to_increment)
				++it;
		}

		return std::vector<std::string>(begin(documents_intersection), end(documents_intersection));	
	}

private:
	std::vector<std::pair<std::string, std::string>> m_documents;
	std::unordered_map<std::string, std::unordered_set<std::string>> m_inverted_index;
};

int main(int argc, char** argv)
{
	InvertedIndex inverted_index{
		{ "hello_document", "You need to write 'Hello world!!!'" },
		{ "technical_document", "You must write without bugs" },
		{ "style_document", "You must to use Google style guide" }
	};

	{
		std::vector<std::string> documents = inverted_index.find_documents_by_text("need google");
		assert((documents == std::vector<std::string>{}));
	}
	{
		std::vector<std::string> documents = inverted_index.find_documents_by_text("unknown");
		assert((documents == std::vector<std::string>{}));
	}
	{
		std::vector<std::string> documents = inverted_index.find_documents_by_text("you");
		assert((documents == std::vector<std::string>{ "hello_document", "style_document", "technical_document" }));
	}
	{
		std::vector<std::string> documents = inverted_index.find_documents_by_text("you must");
		assert((documents == std::vector<std::string>{ "style_document", "technical_document" }));
	}
	{
		std::vector<std::string> documents = inverted_index.find_documents_by_text("you write");
		assert((documents == std::vector<std::string>{ "hello_document", "technical_document" }));
	}
	{
		std::vector<std::string> documents = inverted_index.find_documents_by_text("need to write");
		assert((documents == std::vector<std::string>{ "hello_document" }));
	}

	return EXIT_SUCCESS;
}