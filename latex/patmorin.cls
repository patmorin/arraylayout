%
% The JoCG article class to be used by authors for formatting articles
% appearing in the Journal of Computational Geometry.  The definitive
% version of this file is at http://jocg.org/jocg.cls
%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{patmorin} 
		[2009/05/11 v0.1a
 Pat Morin's article class]

\RequirePackage{fancyhdr}

% Get rid of some article.cls options
\DeclareOption{a4paper}{\OptionNotUsed}
\DeclareOption{a5paper}{\OptionNotUsed}
\DeclareOption{b5paper}{\OptionNotUsed}
\DeclareOption{letterpaper}{\OptionNotUsed}
\DeclareOption{legalpaper}{\OptionNotUsed}
\DeclareOption{executivepaper}{\OptionNotUsed}
\DeclareOption{landscape}{\OptionNotUsed}
\DeclareOption{twoside}{\OptionNotUsed}
\DeclareOption{titlepage}{\OptionNotUsed}
\DeclareOption{onecolumn}{\OptionNotUsed}
\DeclareOption{10pt}{\OptionNotUsed}
\DeclareOption{12pt}{\OptionNotUsed}

% The default action is to pass options to article class
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}

% Process the options
\ProcessOptions

% Read the article class
\LoadClass[11pt,letterpaper]{article}

\RequirePackage{kpfonts}
\RequirePackage[sf,bf,small,raggedright,compact]{titlesec}

% Page setup
\setlength{\textheight}{8.5in}
\setlength{\textwidth}{6in}
\setlength{\topmargin}{-0.375in}
\setlength{\oddsidemargin}{.25in}
\setlength{\evensidemargin}{.25in}
\setlength{\headheight}{0.200in}
\setlength{\headsep}{0.4in}
\setlength{\footskip}{0.500in}
%\setlength{\parskip}{1ex}
\setlength{\parindent}{1.25cm}
%\flushbottom


% Commands for typesetting affiliations and email addresses
\newcommand{\affil}[1]{\textit{#1}}
\newcommand{\email}[1]{\texttt{#1}}

% Maketitle stuff
\renewcommand\maketitle{\par
  \begingroup
    \renewcommand\thefootnote{\@fnsymbol\c@footnote}%
    \def\@makefnmark{\rlap{\@textsuperscript{\normalfont\@thefnmark}}}%
    \long\def\@makefntext##1{\parindent 1em\noindent
            \hb@xt@1.8em{%
                \hss\@textsuperscript{\normalfont\@thefnmark}}##1}%
    \newpage
    \global\@topnum\z@   % Prevents figures from going at top of page.
    \@maketitle
    \@thanks
  \endgroup
  \setcounter{footnote}{0}%
  \global\let\thanks\relax
  \global\let\maketitle\relax
  \global\let\@maketitle\relax
  \global\let\@thanks\@empty
  \global\let\@author\@empty
  \global\let\@date\@empty
  \global\let\@title\@empty
  \global\let\title\relax
  \global\let\author\relax
  \global\let\date\relax
  \global\let\and\relax
}

\renewcommand{\and}{ }

\def\@maketitle{%
  \newpage
  \null
  \newlength{\@gnat}
  \setlength{\@gnat}{2em}
  \addtolength{\@gnat}{-0.4in}
  \vskip \@gnat%
  \begin{flushleft}%
  \let \footnote \thanks
    {\large\sffamily\bfseries \@title   \par}%
    \vskip 1.5em%
    {
      \lineskip .5em%
      {\normalsize\itshape\@author} \\[1em] 
      {\normalsize \@date}
    }%
  \end{flushleft}%
  \par
  \vskip 1em}


% Abstract
\renewenvironment{abstract}
{\hrule\vskip 1ex \noindent\textsc{Abstract.}}{\vskip 1ex \hrule}


%------------- Use this so pdflatex outputs US letter pages -------------
%\usepackage[letterpaper]{hyperref}
\usepackage[dvipsnames]{color}
\definecolor{linkblue}{named}{MidnightBlue}
%\hypersetup{colorlinks=true, linkcolor=linkblue,  anchorcolor=linkblue,
%	citecolor=linkblue, filecolor=linkblue, menucolor=linkblue,
%	urlcolor=linkblue} 


%--------------------------- Headers and Footers ------------------------
\pagestyle{fancy}
\fancyhead{}
\fancyfoot{}
\fancyfoot[c]{\thepage}
%\fancyhead[L]{\sf Journal of Computational Geometry}
%\fancyhead[R]{\texttt{\href{http://jocg.org/}{jocg.org}}}
\renewcommand{\headrulewidth}{1pt}
\renewcommand{\footrulewidth}{1pt}
\pagestyle{fancy}
