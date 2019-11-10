using System;
using System.Collections.Generic;
using System.Linq;

namespace PocketGoogle
{
    public class Indexer : IIndexer
    { 
        private readonly char[] delimiters =
            { ' ', '.', ',', '!', '?', ':', '-', '\r', '\n' };

        private Dictionary<int, string[]> documentsStorage;
        private Dictionary<string, List<int>> indicesStorage;

        public Indexer()
        {
            documentsStorage = new Dictionary<int, string[]>();
            indicesStorage = new Dictionary<string, List<int>>();
        }

        public void Add(int id, string documentText)
        {
            if (documentsStorage.ContainsKey(id))
            {
                throw new ArgumentException();
            }

            var document = documentText.Split(delimiters);

            documentsStorage.Add(id, document);

            foreach (var word in document)
            {
                if (!indicesStorage.ContainsKey(word))
                {
                    var index = new List<int>();
                    index.Add(id);

                    indicesStorage.Add(word, index);
                }
                else
                {
                    if (!indicesStorage[word].Contains(id))
                    {
                        indicesStorage[word].Add(id);
                    }
                }
            }
        }

        public List<int> GetIds(string word)
        {
            if (!indicesStorage.ContainsKey(word))
            {
                throw new ArgumentException();
            }

            var result = indicesStorage[word];
            return result;
        }

        public List<int> GetPositions(int id, string word)
        {
            if (!documentsStorage.ContainsKey(id))
            {
                throw new ArgumentException();
            }

            var result = new List<int>();
            var nextWordPosition = 0;

            foreach (var nextWord in documentsStorage[id])
            {
                if (nextWord == word)
                {
                    result.Add(nextWordPosition);
                }

                nextWordPosition += nextWord.Length + 1;
            }

            return result;
        }

        public void Remove(int id)
        {
            if (!documentsStorage.ContainsKey(id))
            {
                throw new ArgumentException();
            }

            documentsStorage.Remove(id);
        }
    }
}
