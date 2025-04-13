# Setup + Installation
Installing Ruby
```
brew update
brew install rbenv ruby-build
rbenv install 3.2.2
rbenv global 3.2.2
```

Add the following to your `.zshrc` file - use `code ~/.zshrc` to open in VSCode
```
eval "$(rbenv init -)"
export PATH="$HOME/.gem/ruby/3.2.0/bin:$PATH"
```
Then refresh via `source ~/.zshrc`

Install Bundler if needed
```
gem install bundler --user-install
```

Installing RSpec if needed
```
gem install rspec --user-install
```

# Introduction
don't look it's not finished yet

# Features
* <u>Persistence to disk</u>: we can save the database to a file and read it back out again
    * Done via a **pager**, which asks for page number x, and the pager gives us back a block of memory
    * First, it looks in its cache and on a cache miss, it copies data from disk into memory
    * When the user closes the connection to the db, we flush the cache to disk, close the DB file, and free the memory for Pager/Table data structures
* <u>Cursor</u>: represents a location in the table
* <u>B-Tree</u>: Data structure that represents both tables and indexes
    * Each node corresponds to one page, even if it's not full, so no need to handle for partial pages
    * *Order*: each node can have up to m children, where m is the tree's "order"
    * *Nodes with Children*:



# C Trivia
### Difference between `memcpy()` and `strncpy()`

### Unsigned types
When including `#include <stdint.h>`, we have:
* `uint8_t` → unsigned 8-bit integer
* `uint16_t` → unsigned 16-bit integer
* `uint32_t` → unsigned 32-bit integer
* `uint64_t` → unsigned 64-bit integer
