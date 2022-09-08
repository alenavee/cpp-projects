#include "trie.h"


void trie_t::insert(const std::string &str){
    trie_node current = root;
    for(auto ch: str){
      if (current.children[ch]


}




/*   Node current = root
   for c in s
      if current.children[c] ==
         current.children[c] = Node()
      current = current.children[c]
 */

