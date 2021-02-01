#ifndef LAB4_CSVPARSER_H
#define LAB4_CSVPARSER_H

#include <tuple>
#include <vector>
#include <istream>
#include <sstream>
#include <iostream>


enum class QuotesStatement{
    NoQuotedField,
    QuotedField,
    QuotedQuotedField
};


template <class... Args>
class CSVParser {

    std::istream &m_is;
    int m_skip;
    const char row_delim = '\n';
    const char col_delim = ',';
    const char escape = '\"';

    std::string buffer;
    std::tuple<Args...> curTuple;

    std::vector<std::string> readString() {

        QuotesStatement state = QuotesStatement::NoQuotedField;
        std::vector<std::string> fields = {""};

        size_t index = 0;

        getline(m_is, buffer);

        for (size_t i = 0; i < buffer.size(); ++i) {
            switch (state) {

                case QuotesStatement::NoQuotedField:
                    if (buffer[i] == col_delim) {
                        fields.emplace_back("");
                        ++index;
                    } else if (buffer[i] == escape) {
                        state = QuotesStatement::QuotedField;
                        fields[index].push_back(buffer[i]);
                    } else {
                        fields[index].push_back(buffer[i]);
                    }
                    break;

                case QuotesStatement::QuotedField:
                    if (buffer[i] == escape) {
                        fields[index].push_back(buffer[i]);
                        state = QuotesStatement::QuotedQuotedField;
                    } else {
                        fields[index].push_back(buffer[i]);
                    }
                    break;

                case QuotesStatement::QuotedQuotedField:
                    if (buffer[i] == col_delim) {
                        fields.template emplace_back("");
                        ++index;
                        state = QuotesStatement::NoQuotedField;
                    } else if (buffer[i] == escape) {
                        fields[index].push_back(buffer[i]);
                        state = QuotesStatement::QuotedField;
                    } else {
                        state = QuotesStatement::NoQuotedField;
                    }
                    break;
            }

            if (i == buffer.size() - 1) {
                if (sizeof...(Args) == fields.size()){
                    return fields;
                } else if (state == QuotesStatement::QuotedField) {
                    fields[index].push_back(row_delim);
                    getline(m_is, buffer);
                    i = -1;
                } else {
                    throw std::invalid_argument("Wrong syntaxis");
                }
            }
        }

        if (fields.size() == 1){
            throw std::invalid_argument("Empty file");
        }
        return fields;
    }

    template<typename T, typename V>
    void cast(T& a, V& b){
        std::istringstream ss(a);
        ss >> b;
    }

    template<typename T>
    void cast(T& a, T& b){
        b = a;
    }

    template <typename T>
    bool read_tuple_element(std::string& str, T& value) {
        cast(str, value);
        return true;
    }

    template <std::size_t... I>
    std::tuple<Args...> makeTuple(std::vector<std::string>& strings,  std::index_sequence<I...>){
        std::initializer_list<bool>{ read_tuple_element(strings[I], std::get<I>(curTuple))... };
        return curTuple;
    }


    class CSVIterator{
        CSVParser<Args...>& m_parser;
        unsigned int counterStrings = 1;
    public:
        explicit CSVIterator(CSVParser<Args...>& tmp, bool end = false) : m_parser(tmp){
            if (!end) {
                for(auto i = 0; i <= tmp.m_skip; ++(*this), ++i);
            }
        }

        CSVIterator& operator ++(){
            try{
                auto vec = m_parser.readString();
                m_parser.makeTuple(vec, std::make_index_sequence<sizeof...(Args)>());
                ++counterStrings;
            } catch (std::exception&){
                std::cout << "The " << std::to_string(counterStrings) << " string is wrong" << std::endl;
                exit(1);
            }
            return *this;
        }

        std::tuple<Args...>& operator*(){
            return m_parser.curTuple;
        }

        bool operator!=(const CSVIterator& tmp){
            return !m_parser.m_is.fail();
        }
    };

public:
    CSVParser(std::istream& file, int skip) : m_is(file), m_skip(skip){}

    CSVIterator begin(){
        return CSVIterator(*this);
    }

    CSVIterator end(){
        return CSVIterator(*this,true);
    }
};


#endif //LAB4_CSVPARSER_H
