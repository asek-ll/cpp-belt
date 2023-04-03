#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <chrono>
#include <unordered_map>

using namespace std::chrono;

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

//vector<string_view> SplitIntoWords(const string& line) {
//	vector<string_view> result;
//	string_view str(line);
//	while(true) {
//		size_t space_pos = str.find(' ');
//		result.push_back(str.substr(0, space_pos));
//		if(space_pos  == str.npos) {
//			break;
//		} else {
//			str.remove_prefix(space_pos + 1);
//		}
//	}
//
//	return result;
//}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
	int split = 0, input = 0, search = 0, sor = 0, other = 0;
  for (string current_query; getline(query_input, current_query); ) {
	auto start = steady_clock::now();

    const auto words = SplitIntoWords(current_query);

	auto split_end = steady_clock::now();
	split += duration_cast<microseconds>(split_end - start).count();

    unordered_map<size_t, size_t> docid_count;
    for (const auto& word : words) {
      for (const size_t docid : index.Lookup(word)) {
        docid_count[docid]++;
      }
    }

	auto start_search = steady_clock::now();
	input += duration_cast<microseconds>(start_search - split_end).count();

    vector<pair<size_t, size_t>> search_results(
      docid_count.begin(), docid_count.end()
    );
	auto start_sort = steady_clock::now();
	search += duration_cast<microseconds>(start_sort - start_search).count();
    sort(
      begin(search_results),
      end(search_results),
      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        int64_t lhs_docid = lhs.first;
        auto lhs_hit_count = lhs.second;
        int64_t rhs_docid = rhs.first;
        auto rhs_hit_count = rhs.second;
        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
      }
    );
	auto start_out = steady_clock::now();
	sor += duration_cast<microseconds>(start_out - start_sort).count();

    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;

	auto out_end = steady_clock::now();
	other += duration_cast<microseconds>(out_end - start_out).count();
  }
  cout << "split " << split << ", input " << input << ", search " << search << ", sort " << sor << ", other " << other << endl;
}

void InvertedIndex::Add(string document) {
  const size_t docid = docs.size();
  for (auto& word : SplitIntoWords(document)) {
    index[word].push_back(docid);
  }

  docs.push_back(move(document));
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
