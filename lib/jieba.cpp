#include "jieba.h"

int jieba_open(const char* dict_path, const char* hmm_path, const char* user_dict_path, const char* idf_path, const char* stop_word_path)
{
    jieba = new Jieba(dict_path, hmm_path, user_dict_path, idf_path, stop_word_path);

    return 0;
}

void jieba_close()
{
    delete jieba;
    jieba = NULL;
}

AWord* jieba_cut(const char* input, bool with_hmm, size_t* length)
{
    vector<string> result;
    string s(input);
    jieba->Cut(s, result, with_hmm);
    *length = result.size();

    if (result.size() == 0)
    {
        return NULL;
    }

    AWord* words = (AWord*)malloc(sizeof(AWord) * result.size());
    for (size_t i = 0; i < result.size(); i++)
    {
        AWord* word = words + i;
        word->length = result[i].size();
        word->word = new char[result[i].size() + 1];
        memcpy(word->word, result[i].c_str(), result[i].size());
        word->word[result[i].size()] = 0;
    }

    return words;
}

void jieba_free(AWord* words, size_t length)
{
    if ((words == NULL) || (length == 0))
    {
        return;
    }

    for (size_t i = 0; i < length; i++)
    {
        AWord* word = words + i;
        delete[] word->word;
        word->word = NULL;
    }

    free(words);
    words = NULL;
}
