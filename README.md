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