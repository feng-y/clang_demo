set nu
set nu
set mouse=a
set ts=2
set smartindent
set shiftwidth=2
set nu
set mouse=a
set autoindent
set cindent
set tabstop=2 shiftwidth=2 expandtab
set updatetime=500

" Ignore case when searching
set ignorecase
" When searching try to be smart about cases
set smartcase
" Highlight search results
set hlsearch
set tabstop=2 " tab 长度设置为 4
set nobackup " 覆盖文件时不备份
set cursorline " 突出显示当前行
set ruler " 在右下角显示光标位置的状态行
set autoindent " 自动缩进

call plug#begin('~/.vim/plugged')
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'junegunn/fzf'
Plug 'junegunn/fzf.vim'
Plug 'tpope/vim-surround'
Plug 'Raimondi/delimitMate'
Plug 'vim-scripts/a.vim'
Plug 'vim-syntastic/syntastic'
Plug 'easymotion/vim-easymotion'
Plug 'jremmen/vim-ripgrep'

Plug 'mhinz/vim-startify'
Plug 'hotoo/pangu.vim'
Plug 'itchyny/lightline.vim'
Plug 'majutsushi/tagbar'
Plug 'scrooloose/nerdtree'
Plug 'Xuyuanp/nerdtree-git-plugin'
Plug 'rking/ag.vim'
Plug 'tmhedberg/SimpylFold'
Plug 'lfv89/vim-interestingwords'
Plug 'Valloric/dotfiles'
Plug 'icymind/NeoSolarized'
Plug 'seebi/dircolors-solarized'
Plug 'scrooloose/nerdcommenter'
Plug 'altercation/vim-colors-solarized'

Plug 'junegunn/vim-plug'
Plug 'mhinz/vim-signify'
Plug 'kana/vim-operator-user'
Plug 'rhysd/vim-clang-format'
Plug 'vim-scripts/vcscommand.vim'

" 定义插件，默认用法，和 Vundle 的语法差不多
Plug 'junegunn/vim-easy-align'
Plug 'skywind3000/quickmenu.vim'
" " 延迟按需加载，使用到命令的时候再加载或者打开对应文件类型才加载
Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
Plug 'tpope/vim-fireplace', { 'for': 'clojure' }
" " 确定插件仓库中的分支或者 tag
" Plug 'rdnetto/YCM-Generator', { 'branch': 'stable' }

" 动态检查
" Plug 'w0rp/ale'
Plug 'mhinz/vim-signify'
Plug 'pseewald/vim-anyfold'
Plug 'Yggdroot/indentLine'
Plug 'jiangmiao/auto-pairs'
Plug 'mileszs/ack.vim'
Plug 'nathanaelkane/vim-indent-guides'
Plug 'prabirshrestha/async.vim'
call plug#end()


let g:clang_format#command='/opt/tiger/bytelinter/thirdparty/llvm11/bin/clang-format'
let g:clang_format#code_style='google'
let g:clang_format#style_options = {
            \ "AccessModifierOffset" : -1,
            \ "IndentWidth" : 2,
            \ "ColumnLimit" : 110,
            \ "DerivePointerAlignment" : "false",
            \ "PointerAlignment" : "Left",
            \ "ReferenceAlignment" : "Left",
            \ "BinPackArguments" : "false",
            \ "BinPackParameters" : "false",
            \ "AllowShortIfStatementsOnASingleLine" : "false",
            \ "AlwaysBreakTemplateDeclarations" : "false",
            \ "FixNamespaceComments":"true1",
            \ "Standard" : "C++11",
            \ "AlignConsecutiveDeclarations" :  "false",
            \ "AllowShortBlocksOnASingleLine" : "false",
            \ "AllowShortFunctionsOnASingleLine" : "false",
            \ "AllowShortCaseLabelsOnASingleLine" : "false",
            \ "AlwaysBreakBeforeMultilineStrings": "true",
            \ "AllowAllParametersOfDeclarationOnNextLine" : "true",
            \ "AlignConsecutiveAssignments" : "false",
            \ "AlignTrailingComments" : "true",
            \ "BreakBeforeTernaryOperators": "true",
            \ "MaxEmptyLinesToKeep" : 1,
            \}

" map to <Leader>cf in C++ code
autocmd FileType c,cpp,objc nnoremap <buffer><Leader>cf :<C-u>ClangFormat<CR>
autocmd FileType c,cpp,objc vnoremap <buffer><Leader>cf :ClangFormat<CR>
" if you install vim-operator-user
autocmd FileType c,cpp,objc map <buffer><Leader>x <Plug>(operator-clang-format)
" Toggle auto formatting:
nmap <Leader>C :ClangFormatAutoToggle<CR>
