git clone ssh://git.wherever.com/git/all.git
cd all
git submodule update –init
git submodule foreach git checkout master

