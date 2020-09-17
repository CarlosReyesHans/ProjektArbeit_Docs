%%
%% This is file 'tuhhthesis.cls'
%%
%% Copyright 2009 Christian Renner, Christoph Weyer
%%
%% This file is part of the TUHH-Script-bundle.
%%
%% This system is distributed in the hope that it will be useful,
%% but WITHOUT ANY WARRANTY; without even the implied warranty of
%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
%%

\NeedsTeXFormat{LaTeX2e}[2009/09/24]
\RequirePackage{svn-multi}[2011/08/20]
\svnid{$Id: tuhhthesis.cls 42772 2019-06-28 12:21:48Z ti5cw $}

\makeatletter

\def\tuhh@ClassName{tuhhthesis}
\def\tuhh@ClassDesc{TUHH thesis class}
\def\tuhh@ClassVersion{0.3.6}
\def\tuhh@ClassFullVersion{\tuhh@ClassVersion\space(rev\space\svnfilerev)}

\ProvidesClass{\tuhh@ClassName}[%
  \svnfileyear/\svnfilemonth/\svnfileday\space%
  v\tuhh@ClassFullVersion\space\tuhh@ClassDesc%
  ^^J\@spaces\@spaces\@spaces\@spaces\space\space
  Copyright (C) Christian Renner and Christoph Weyer, 2009-\svnfileyear^^J]

%%% using kev/value pairs as options to packages and classes
\RequirePackage{kvoptions}

\SetupKeyvalOptions{%
  family=tuhhthesis,
  prefix=@tuhhthesis@
}

\DeclareBoolOption{abstract}

\DeclareBoolOption{declaration}

\DeclareBoolOption{acknowledgment}

\DeclareBoolOption{symbollist}
\DeclareBoolOption{figurelist}
\DeclareBoolOption{tablelist}

\DeclareBoolOption{index}

\DeclareBoolOption{ownpub}

\DeclareBoolOption{cv}

\DeclareBoolOption{bibbacklinks}

\DeclareBoolOption{publishsize}

\DeclareBoolOption{approved}
% TODO should only be used with phdthesis type

\DeclareStringOption[11pt]{fontsize}

\DeclareDefaultOption{%
  \PassOptionsToPackage{\CurrentOption}{tuhhpreamble}%
}
\ProcessKeyvalOptions*\relax%

%%% configure underlying packages
%% hyperref
\PassOptionsToPackage{pdfpagelayout=SinglePage}{hyperref}%
\PassOptionsToPackage{pdfpagemode=UseOutlines}{hyperref}%
\PassOptionsToPackage{bookmarksopen=true}{hyperref}%
\PassOptionsToPackage{bookmarksopenlevel={1}}{hyperref}%
\PassOptionsToPackage{bookmarksnumbered=true}{hyperref}%
\if@tuhhthesis@index%
  \PassOptionsToPackage{hyperindex}{hyperref}
\fi
%% scrbook
\PassOptionsToClass{fontsize=\@tuhhthesis@fontsize}{scrbook}
\PassOptionsToClass{numbers=noendperiod}{scrbook}
\if@tuhhthesis@publishsize%
  % FIXME has no influence ...
  %\PassOptionsToClass{a5paper,twoside,DIV=14,BCOR=15mm}{scrbook}
  \PassOptionsToClass{a5paper,twoside}{scrbook}
\else
  \PassOptionsToClass{a4paper,twoside,DIV=12,BCOR=25mm}{scrbook}
\fi
\PassOptionsToClass{cleardoublepage=current}{scrbook}
\PassOptionsToClass{chapterprefix=true}{scrbook}
\PassOptionsToClass{headsepline}{scrbook}
\PassOptionsToClass{bibliography=totoc}{scrbook}
\if@tuhhthesis@index%
  \PassOptionsToClass{index=totoc}{scrbook}
\fi
\if@tuhhthesis@bibbacklinks%
  \PassOptionsToPackage{pagebackref}{hyperref}
\fi

% first load pre-class definitions
\RequirePackage{tuhhpreclassdefs}

% than load the underlying class
\LoadClass{scrbook}

% give some credits to scrbook in created pdf file
\def\tuhh@ClassFullVersion{\tuhh@ClassVersion\space(rev\space\svnfilerev) using class \KOMAClassName~version \KOMAScriptVersion}

% then load the TUHH packages
\RequirePackage{tuhhpreamble}

% load set of common commands for thesis, report, et al.
\RequirePackage{tuhhbookdef}
\RequirePackage{tuhhtubdok}

%%% find a good place
\if@tuhhthesis@index%
  \RequirePackage{makeidx}
  \newcommand*{\main}[1]{\textbf{\hyperpage{#1}}}
  \newcommand{\idxdef}[1]{\emph{#1}\index{#1}}  % define an index entry
  \newcommand{\idx}[1]{{#1}\index{#1}}  % reference an indexed entry
  \newcommand{\idxrdef}[2]{\emph{#1}\index{#2}}  % define an index entry
  \newcommand{\idxr}[2]{{#1}\index{#2}}  % reference an indexed entry
\fi%

% ownpub style
\if@tuhhthesis@ownpub%
  \if@english%
    \def\tuhhDefaultBSTStyleOwnpub{tuhhunsrt}
  \else
    \def\tuhhDefaultBSTStyleOwnpub{tuhhunsrtdin}
%  \if@german%
%    \def\tuhhDefaultBSTStyleOwnpub{tuhhplainyr}
%  \else
%    \def\tuhhDefaultBSTStyleOwnpub{tuhhplainyr}
%  \fi
  \fi
\fi


%%%
%%% CONFIGURATION
%%%

% title page fonts
\newcommand*{\tuhhthesis@fnt@titlepage}{\normalfont\sffamily\LARGE}
\setkomafont{subject}{\bfseries\color{tuhh_mediumgray}}
\setkomafont{title}{\Huge\bfseries\color{tuhh_color_title}}
\@ifundefined{IfExistskomafont}{
  \newkomafont{author}{}
  \newkomafont{date}{}
}{
  \IfExistskomafont{author}{}{
    \newkomafont{author}{}
  }
  \IfExistskomafont{date}{}{
    \newkomafont{date}{}
  }
}

\newkomafont{prelude}{\normalfont\sffamily\LARGE\bfseries\color{tuhh_mediumgray}}

% student version
\newkomafont{descr}{\large\color{tuhh_darkgray}}

\newkomafont{supervisorName}{\normalsize\color{tuhh_black}}
\newkomafont{supervisorAddr}{\small\color{tuhh_black}}
\newkomafont{examinerName}{\large}
\newkomafont{examinerAddr}{\normalsize}

% phd version (currently overwriting everything)
\newkomafont{examinerDescr}{\normalsize\color{tuhh_darkgray}}
\setkomafont{examinerName}{\normalsize}
\setkomafont{examinerAddr}{\small}


%%% title page positioning
\newlength{\tuhhthesis@typePosY}
\newlength{\tuhhthesis@titlePosY}
\newlength{\tuhhthesis@authorPosY}
\newlength{\tuhhthesis@datePosY}
\newlength{\tuhhthesis@supervisorPosY}
\newlength{\tuhhthesis@examinerPosY}

\setlength{\tuhhthesis@typePosY}{0.16\paperheight}             % y center
\setlength{\tuhhthesis@titlePosY}{0.30\paperheight}            % ...
\setlength{\tuhhthesis@authorPosY}{0.39\paperheight}           % ...
\setlength{\tuhhthesis@datePosY}{0.50\paperheight}             % ...
\setlength{\tuhhthesis@supervisorPosY}{0.61\paperheight}       % y center
\setlength{\tuhhthesis@examinerPosY}{0.77\paperheight}         % y bottom

\if@tuhhthesis@bibbacklinks%
  \renewcommand*{\backref}[1]{}
  \renewcommand*{\backrefalt}[4]{{\footnotesize\textcolor{tuhh_gray!35!tuhh_blue}{%
    \ifcase #1 %
      \or Cited on page~#2.%
    \else Cited on pages~#2.%
    \fi%
  }}}
\fi

%%%
%%% COMMANDS
%%%

%%% thesis related data
\newif\if@tuhhthesis@submitDate
\@tuhhthesis@submitDatefalse
\newif\if@tuhhthesis@examinationDate
\@tuhhthesis@examinationDatefalse
\newif\if@tuhhthesis@matrNumber
\@tuhhthesis@matrNumberfalse
\newif\if@tuhhthesis@course
\@tuhhthesis@coursefalse

\def\tuhhthesis@course{\unset}
\def\tuhhthesis@matrnumber{\unset}

\newcommand{\submitdate}[1]{%
  \@tuhhthesis@submitDatetrue%
  \setdate{#1}
}

% phd-only
\newcommand{\examinationdate}[1]{%
  \@tuhhthesis@examinationDatetrue%
  \setdate{#1}
}

\newcommand{\course}[1]{%
  \@tuhhthesis@coursetrue%
  \def\tuhhthesis@course{#1}
}

\newcommand{\matrnumber}[1]{%
  \@tuhhthesis@matrNumbertrue%
  \def\tuhhthesis@matrnumber{#1}
}


%%%
%%% INTERNAL VARIABLES
%%%
\def\tuhhthesis@type{unset}

\def\@tuhhthesis@phdType{Doktor-Ingenieur\if@tuhhthesis@authorIsMale\else in\fi~(Dr.-Ing.)}
\def\@tuhhthesis@birthplace{unset}

\def\tuhhthesis@supervisorFirst@Name{unset}
\def\tuhhthesis@supervisorFirst@Addr{unset}
\def\tuhhthesis@supervisorSecond@Name{unset}
\def\tuhhthesis@supervisorSecond@Addr{unset}

\def\tuhhthesis@examinationChair@Name{unset}
\def\tuhhthesis@examinationChair@Addr{unset}

\def\tuhhthesis@examinerFirst@Name{unset}
\def\tuhhthesis@examinerFirst@Addr{unset}
\def\tuhhthesis@examinerSecond@Name{unset}
\def\tuhhthesis@examinerSecond@Addr{unset}
\def\tuhhthesis@examinerThird@Name{unset}
\def\tuhhthesis@examinerThird@Addr{unset}

\newif\if@tuhhthesis@supervisorFirst
\@tuhhthesis@supervisorFirstfalse
\newif\if@tuhhthesis@supervisorSecond
\@tuhhthesis@supervisorSecondfalse

\newif\if@tuhhthesis@examinationChair
\@tuhhthesis@examinationChairfalse
\newif\if@tuhhthesis@examinerFirst
\@tuhhthesis@examinerFirstfalse
\newif\if@tuhhthesis@examinerSecond
\@tuhhthesis@examinerSecondfalse
\newif\if@tuhhthesis@examinerThird
\@tuhhthesis@examinerThirdfalse

\newif\if@tuhhthesis@authorIsMale
\@tuhhthesis@authorIsMaletrue


%%%
%%% extend the language tag database for local purposes
%%%
%%% LANGUAGE: German
\RequirePackage{tuhhlang}
\if@german%
    \def\TUHHLANG@AuthorBy{von}
    \def\TUHHLANG@Supervised{Betreut von}
    \def\TUHHLANG@ExaminerFirst{Erstpr{\"u}fer}
    \def\TUHHLANG@ExaminerSecond{Zweitpr{\"u}fer}
    \def\TUHHLANG@ExaminerThird{Drittpr{\"u}fer}
    \def\TUHHLANG@Titlepage{Titelseite}
    \def\TUHHLANG@TocName{Inhaltsverzeichnis}
    \def\TUHHLANG@Acknowledgment{Danksagung}
    \def\TUHHLANG@ListOfSymbols{Verwendete Symbole}
    \def\TUHHLANG@Abstract{Abstract}
    \def\TUHHLANG@DeclarationCandidate{Eidesstattliche Erkl{\"a}rung}
    \def\TUHHLANG@Cv{Lebenslauf}
    \def\TUHHLANG@OwnPub{Eigene Publikationen}
    \def\TUHHLANG@phdDefenseDate{Tag der m{\"u}ndlichen Pr{\"u}fung}
    \def\TUHHLANG@ExaminationChair{Vorsitz des Pr{\"u}fungsausschusses}
\fi
%%% LANGUAGE: English
\if@english%
    \def\TUHHLANG@AuthorBy{by}
    \def\TUHHLANG@Supervised{Supervised by}
    \def\TUHHLANG@ExaminerFirst{First Examiner}
    \def\TUHHLANG@ExaminerSecond{Second Examiner}
    \def\TUHHLANG@ExaminerThird{Third Examiner}
    \def\TUHHLANG@Titlepage{Titlepage}
    \def\TUHHLANG@TocName{Table of Contents}
    \def\TUHHLANG@Acknowledgment{Acknowledgment}
    \def\TUHHLANG@Abstract{Abstract}
    \def\TUHHLANG@ListOfSymbols{List of Symbols}
    \def\TUHHLANG@DeclarationCandidate{Declaration by Candidate}
    \def\TUHHLANG@Cv{Curriculum Vitae}
    \def\TUHHLANG@OwnPub{Author's Publications}
    \def\TUHHLANG@phdDefenseDate{Date of Oral Examination}
    \def\TUHHLANG@ExaminationChair{Chair of Examination Board}
\fi

%%%
%%% INTERNAL COMMANDS
%%%
\newcommand{\tuhhthesis@checkParameters}{%
  \ifthenelse{\equal{\tuhhthesis@type}{phd}}{%
    \if@tuhhthesis@approved%
      \if@tuhhthesis@examinationDate%
      \else%
        \ClassError{\tuhh@ClassName}{Examination Date not provided}\relax%
      \fi%
      \if@tuhhthesis@examinationChair%
      \else%
        \ClassError{\tuhh@ClassName}{Examination Chair not provided}\relax%
      \fi%
      \if@tuhhthesis@examinerSecond%
      \else%
        \ClassError{\tuhh@ClassName}{No Second Examiner defined}\relax%
      \fi%
    \else%
      \if@tuhhthesis@supervisorFirst%
      \else%
        \ClassError{\tuhh@ClassName}{No Supervisor defined}\relax%
      \fi%
    \fi
  }{%
    \if@tuhhthesis@examinerFirst%
    \else%
      \ClassError{\tuhh@ClassName}{No Examiner defined}\relax%
    \fi%

    \if@tuhhthesis@submitDate%
    \else%
      \ClassError{\tuhh@ClassName}{Submission Date not provided}\relax%
    \fi%
  }

  % the following parameters are onyl necessary with student theses
  \ifthenelse{\equal{\tuhhthesis@type}{student}}{%
    \if@tuhhthesis@matrNumber%
    \else%
      \ClassError{\tuhh@ClassName}{Matriculation Number not provided}\relax%
    \fi%

    \if@tuhhthesis@course%
    \else%
      \ClassError{\tuhh@ClassName}{Course of Studies not provided}\relax%
    \fi%
  }{%
    \ifthenelse{\equal{\@tuhhthesis@birthplace}{unset}}{%
      \ClassError{\tuhh@ClassName}{Birthplace of author is not provided}\relax%
    }{%
    }%
  }%
}

\newcommand{\preludeCaption}[1]{%
  \phantomsection%
  \noindent{\usekomafont{prelude}{#1}}\par\vspace{0.5cm}\par\relax
}



\newsavebox{\tuhh@titleBox}
\newcommand{\tuhhthesis@saveTitleBox}{%
   % save the title into the title box
   \begin{lrbox}{\tuhh@titleBox}%
      \begin{minipage}{\textwidth}\begin{center}%
         \tuhhthesis@fnt@titlepage\usekomafont{title}%
         \tuhhpreamble@title%
      \end{center}\end{minipage}%
   \end{lrbox}%
}

\newsavebox{\tuhh@phdBox}
\newcommand{\tuhhthesis@savePhDBox}{%
   % save the PhD info into the PhD box
   \begin{lrbox}{\tuhh@phdBox}%
      \begin{minipage}{\textwidth}\begin{center}%
         \tuhhthesis@fnt@titlepage\usekomafont{descr}%
         \if@tuhhthesis@approved%
           Vom Promotionsausschuss der\\
           Technischen Universit{\"a}t Hamburg\\[1.3em]
           zur Erlangung des akademischen Grades\\[1.3em]
           \@tuhhthesis@phdType\\[1.3em]
           genehmigte Dissertation
         \else
           Dem Promotionsausschuss der\\
           Technischen Universit{\"a}t Hamburg\\[1.3em]
           zur Erlangung des akademischen Grades\\[1.3em]
           \@tuhhthesis@phdType\\[1em]
           vorgelegte Dissertation
         \fi
      \end{center}\end{minipage}%
   \end{lrbox}%
}

\newsavebox{\tuhh@phdSupervisorBox}
\newcommand{\tuhhthesis@savePhDSupervisorBox}{%
   % save the PhD info into the PhD box
   \begin{lrbox}{\tuhh@phdSupervisorBox}%
      \begin{minipage}{\textwidth}%
         \tuhhthesis@fnt@titlepage\usekomafont{descr}%
         Betreuer: \tuhhthesis@supervisorFirst@Name
      \end{minipage}%
   \end{lrbox}%
}

\newsavebox{\tuhh@supervisorBox}
\newcommand{\tuhhthesis@saveSupervisorBox}{%
   \if@tuhhthesis@supervisorFirst%
     % save into box
     \begin{lrbox}{\tuhh@supervisorBox}%
       \begin{minipage}{\textwidth}\begin{center}%
          % by
          \tuhhthesis@fnt@titlepage\usekomafont{descr}%
          \tuhh@printTag{Supervised}%
          % supervisors
          %   first
          \vskip.8\baselineskip
          \tuhhthesis@fnt@titlepage\usekomafont{supervisorName}%
          \tuhhthesis@supervisorFirst@Name\\%
          \tuhhthesis@fnt@titlepage\usekomafont{supervisorAddr}%
          \quad\tuhhthesis@supervisorFirst@Addr%
          % second (if provided)
          \if@tuhhthesis@supervisorSecond%
            \vskip1\baselineskip
            \tuhhthesis@fnt@titlepage\usekomafont{supervisorName}%
            \tuhhthesis@supervisorSecond@Name\\%
            \tuhhthesis@fnt@titlepage\usekomafont{supervisorAddr}%
            \quad\tuhhthesis@supervisorSecond@Addr%
          \fi%
       \end{center}\end{minipage}%
     \end{lrbox}%
   \fi%
}

\newsavebox{\tuhh@phdExaminationBox}
\newcommand{\tuhhthesis@savePhDExaminationBox}{%
   \begin{lrbox}{\tuhh@phdExaminationBox}%
     \centering
     \begin{tabular}{rp{0.7\textwidth}}
       % date of examination
        \multicolumn{1}{r|}{\usekomafont{examinerDescr}%
          \tuhh@printTag{phdDefenseDate}} &
        \usekomafont{examinerName}\printdate \\
        % chair
        & \\% <-- leave blank to create little vertical gap
        \multicolumn{1}{r|}{\usekomafont{examinerDescr}%
          \tuhh@printTag{ExaminationChair}} &%
        \usekomafont{examinerName}%
        \tuhhthesis@examinationChair@Name\vskip0.8ex%
        \usekomafont{examinerAddr}%
        \tuhhthesis@examinationChair@Addr \\
        % first examiner
        & \\% <-- leave blank to create little vertical gap
        \multicolumn{1}{r|}{\usekomafont{examinerDescr}%
          \tuhh@printTag{ExaminerFirst}} &%
        \usekomafont{examinerName}%
        \tuhhthesis@examinerFirst@Name\vskip0.8ex%
        \usekomafont{examinerAddr}%
        \tuhhthesis@examinerFirst@Addr \\
        % second examiner
        & \\% <-- leave blank to create little vertical gap
        \multicolumn{1}{r|}{\usekomafont{examinerDescr}%
          \tuhh@printTag{ExaminerSecond}} &%
        \usekomafont{examinerName}%
        \tuhhthesis@examinerSecond@Name\vskip0.8ex%
        \usekomafont{examinerAddr}%
        \tuhhthesis@examinerSecond@Addr \\
        % third examiner (if any)
        \if@tuhhthesis@examinerThird%
          & \\% <-- leave blank to create little vertical gap
          \multicolumn{1}{r|}{\usekomafont{examinerDescr}%
            \tuhh@printTag{ExaminerThird}} &%
          \usekomafont{examinerName}%
          \tuhhthesis@examinerThird@Name\vskip0.8ex%
          \usekomafont{examinerAddr}%
          \tuhhthesis@examinerThird@Addr \\
        \fi
     \end{tabular}
   \end{lrbox}
}

\newsavebox{\tuhh@examinerBox}
\newcommand{\tuhhthesis@saveExaminerBox}{%
   \begin{lrbox}{\tuhh@examinerBox}%
     \centering
     \begin{tabular}{p{0.3\textwidth}p{0.65\textwidth}}
     %\begin{minipage}{\textwidth}\begin{center}%
        % first
        \multicolumn{1}{r|}{\tuhhthesis@fnt@titlepage\usekomafont{descr}%
        \tuhh@printTag{ExaminerFirst}} &%
        \tuhhthesis@fnt@titlepage\usekomafont{examinerName}%
        \tuhhthesis@examinerFirst@Name\vskip2mm%
        \tuhhthesis@fnt@titlepage\usekomafont{examinerAddr}%
        \tuhhthesis@examinerFirst@Addr \\%
        % second (if provided)
        \if@tuhhthesis@examinerSecond%
          & \\% <-- leave blank to create little vertical gap
          \multicolumn{1}{r|}{\tuhhthesis@fnt@titlepage\usekomafont{descr}%
          \tuhh@printTag{ExaminerSecond}} &%
          \tuhhthesis@fnt@titlepage\usekomafont{examinerName}%
          \tuhhthesis@examinerSecond@Name\vskip2mm%
          \tuhhthesis@fnt@titlepage\usekomafont{examinerAddr}%
          \tuhhthesis@examinerSecond@Addr \\%
        \fi%
        % second (if provided)
        \if@tuhhthesis@examinerThird%
          & \\% <-- leave blank to create little vertical gap
          \multicolumn{1}{r|}{\tuhhthesis@fnt@titlepage\usekomafont{descr}%
          \tuhh@printTag{ExaminerThird}} &%
          \tuhhthesis@fnt@titlepage\usekomafont{examinerName}%
          \tuhhthesis@examinerThird@Name\vskip2mm%
          \tuhhthesis@fnt@titlepage\usekomafont{examinerAddr}%
          \tuhhthesis@examinerThird@Addr \\%
        \fi%
     \end{tabular}%
    \end{lrbox}%
}


%%%
%%% GLOBAL VARIABLES
%%%


%%%
%%% GLOBAL COMMANDS
%%%
\if@tuhhpreamble@preview
\else
\AtBeginDocument{%

	%for the cv
%	\settowidth{\cvlabelwidth}{%
%		\cvlabelfont This is my longest label indeed%
%	}%

  \begin{singlespacing}
  % check if all paprameters are set
  \tuhhthesis@checkParameters

  % add some more pieces of information to the PDF keywords
  % TODO
  \addtokeywords{\tuhhpreamble@subject}%

  % save type, title, and contact box
  \tuhhthesis@saveTitleBox
  \ifthenelse{\equal{\tuhhthesis@type}{student}}{%
    \tuhhthesis@saveSupervisorBox
    \tuhhthesis@saveExaminerBox
  }{%
    \tuhhthesis@savePhDBox
    \if@tuhhthesis@approved%
      \tuhhthesis@savePhDExaminationBox
    \else%
      \tuhhthesis@savePhDSupervisorBox
    \fi%
  }

  % make the titlepage
  \pagestyle{empty}%
  \pagenumbering{alph}
  \ifthenelse{\equal{\tuhhthesis@type}{student}}{%
    \hypertarget{tuhhthesis@titlepage}{\makeStudentTitlePage}
  }{%
    \hypertarget{tuhhthesis@titlepage}{\makePhDTitlePage}
  }
  \printTUBDokNumberOnCurrentPage
  \pdfbookmark[0]{\tuhh@printTag{Titlepage}}{tuhhthesis@titlepage}

  % print examiner information on extra page (PhD-only)
  \ifthenelse{\equal{\tuhhthesis@type}{student}}{}{%
    \if@tuhhthesis@approved%
      \clearpage
      \makePhDSecondPage
    \fi
  }
  \cleardoublepage

  % make acknowledgment
  \if@tuhhthesis@acknowledgment%
    \IfFileExists{prelude_acknowledgment}{%
      \pdfbookmark[0]{\tuhh@printTag{Acknowledgment}}{tuhhthesis@acknowledgment}
      \preludeCaption{\hypertarget{tuhhthesis@acknowledgment}{\tuhh@printTag{Acknowledgment}}}
      \noindent \input{prelude_acknowledgment}
      \cleardoublepage
    }{%
      \ClassError{\tuhh@ClassName}{Option 'acknowledgment' is given, but file 'prelude_acknowledgment.tex' is missing.}
    }%
  \fi

%	  % make cv
%  \if@tuhhthesis@cv%
%    \IfFileExists{postlude_cv}{%
%      \pdfbookmark[0]{\tuhh@printTag{Cv}}{tuhhthesis@Cv}
%      \preludeCaption{\hypertarget{tuhhthesis@cv}{\tuhh@printTag{Cv}}}
%      \noindent \input{postlude_cv}
%      \cleardoublepage
%    }{%
%      \ClassError{\tuhh@ClassName}{Option 'cv' is given, but file
%      'postlude_cv.tex' is missing.} }%
%  \fi


  % make the declaration by candidate
  \if@tuhhthesis@declaration%
     \pdfbookmark[0]{\tuhh@printTag{DeclarationCandidate}}{tuhhthesis@declaration}
     \preludeCaption{\hypertarget{tuhhthesis@declaration}{\tuhh@printTag{DeclarationCandidate}}}
     \if@german%
       \input{prelude_declaration.de}
     \else%
       \input{prelude_declaration.en}
     \fi
     \cleardoublepage
  \fi

  % make abstract
  \if@tuhhthesis@abstract%
    \IfFileExists{prelude_abstract}{%
      \pdfbookmark[0]{\tuhh@printTag{Abstract}}{tuhhthesis@abstract}
      \preludeCaption{\hypertarget{tuhhthesis@abstract}{\tuhh@printTag{Abstract}}}
      \noindent\input{prelude_abstract}
      \cleardoublepage
    }{%
      \ClassError{\tuhh@ClassName}{Option 'abstract' is given, but file 'prelude_abstract.tex' is missing.}
    }%
  \fi


  % start frontmatter

  %%%
  % start the real content of the work (prelude)
  \frontmatter
  \pagestyle{scrheadings}

  %% toc
  \hypertarget{tuhhthesis@toc}{}
  \pdfbookmark[0]{\tuhh@printTag{TocName}}{tuhhthesis@toc}
  \renewcommand\contentsname{\tuhh@printTag{TocName}}
  \tableofcontents
  \cleardoublepage

  % list of figures
  \if@tuhhthesis@figurelist%
    %\hypertarget{tuhhthesis@lof}{}
    %\pdfbookmark[0]{\tuhh@printTag{LofName}}{tuhhthesis@lof}
    \renewcommand\contentsname{\tuhh@printTag{LofName}}
    \listoffigures
    \addcontentsline{toc}{chapter}{\tuhh@printTag{LofName}}
    \cleardoublepage
  \fi

  % list of tables
  \if@tuhhthesis@tablelist%
    %\hypertarget{tuhhthesis@lot}{}
    %\pdfbookmark[0]{\tuhh@printTag{LotName}}{tuhhthesis@lot}
    \renewcommand\contentsname{\tuhh@printTag{LotName}}
    \listoftables
    \addcontentsline{toc}{chapter}{\tuhh@printTag{LotName}}
    \cleardoublepage
  \fi

  % TODO table of listings?

  % list of symbols
  \if@tuhhthesis@symbollist%
    \IfFileExists{prelude_symbols}{%
      \phantomsection%prevents "Warning: No destination for bookmark of \addcontentsline"
      \addchap{\tuhh@printTag{ListOfSymbols}}\label{cha:listOfSymbols}
      \input{prelude_symbols}
      \cleardoublepage
    }{%
      \ClassError{\tuhh@ClassName}{Option 'symbollist' is given, but file 'prelude_symbols.tex' is missing.}
    }%
  \fi


  % and now comes the student's content
  \end{singlespacing}
  \mainmatter
}
\fi

\if@tuhhthesis@ownpub%
  \RequirePackage{multibib}
  \newcites{ownpub}{\tuhh@printTag{OwnPub}}
  \AtEndDocument{%
    \IfFileExists{ownpub.bib}{%
      \thispagestyle{empty}
      %\preludeCaption{\hypertarget{tuhhthesis@cv}{\tuhh@printTag{OwnPub}}}
      \begin{singlespacing}
        \small
        \frenchspacing
        \bibliographystyleownpub{\tuhhDefaultBSTStyleOwnpub}
        \bibliographyownpub{ownpub}
        \nociteownpub{*}
      \end{singlespacing}
      \cleardoublepage
    }{%
      \ClassError{\tuhh@ClassName}{Option 'ownpub' is given, but file
      	'ownpub.bib' is missing.}
    }%
  }
\fi

%\if@tuhhpreamble@preview
%\else
\if@tuhhthesis@cv%
  \RequirePackage{currvita}
  \AtEndDocument{%
    \setlength{\cvlabelwidth}{0.25\textwidth}
    \renewcommand*{\cvlistheadingfont}{\normalfont\sffamily\large\color{tuhh_blue}}
    \renewcommand*{\cvlabelfont}{\normalfont\rmfamily\normalsize\color{tuhh_darkgray}}
    % make cv
    \IfFileExists{postlude_cv}{%
      \pagestyle{empty}
      %\pdfbookmark[0]{\tuhh@printTag{Cv}}{tuhhthesis@Cv}
      \preludeCaption{\hypertarget{tuhhthesis@cv}{\tuhh@printTag{Cv}}}
      \addcontentsline{toc}{chapter}{\tuhh@printTag{Cv}}
      \noindent\input{postlude_cv}
      \cleardoublepage
    }{%
      \ClassError{\tuhh@ClassName}{Option 'cv' is given, but file
      'postlude_cv.tex' is missing.}
    }%
	}
\fi
%\fi

%%%
%%% Command: \setthesistype
%%%
\newcommand{\setthesistype}[1]{%
  \ifthenelse{\equal{#1}{projectwork}}{
    \subject{\tuhh@printTag{ProjectWork}}
    \def\tuhhthesis@type{student}
  }{
    \ifthenelse{\equal{#1}{bachelorthesis}}{
      \subject{\tuhh@printTag{BachelorThesis}}
      \def\tuhhthesis@type{student}
    }{
      \ifthenelse{\equal{#1}{masterthesis}}{
        \subject{\tuhh@printTag{MasterThesis}}
        \def\tuhhthesis@type{student}
      }{
        \ifthenelse{\equal{#1}{diplomathesis}}{
          \subject{\tuhh@printTag{DiplomaThesis}}
          \def\tuhhthesis@type{student}
        }{
          \ifthenelse{\equal{#1}{phdthesis}}{
            % FIXME is there any difference between phdthesis and dissertation?
            \subject{\tuhh@printTag{PhDThesis}}
            \def\tuhhthesis@type{phd}
          }{
            \ifthenelse{\equal{#1}{dissertation}}{
              \subject{\tuhh@printTag{Dissertation}}
              \def\tuhhthesis@type{phd}
            }{
              \ClassError{\tuhh@ClassName}{thesis type '#1' unknown}
            }
          }
        }
      }
    }
  }
}

%%%
%%% Command: \setSexOfAuthor
%%% sets the sex of the author (male/female)
%%%
\newcommand{\setSexOfAuthor}[1]{%
  \ifthenelse{\equal{\tuhhthesis@type}{phd}}{%
    \ifthenelse{\equal{#1}{male}}{%
      \@tuhhthesis@authorIsMaletrue
    }{%
      \ifthenelse{\equal{#1}{female}}{%
        \@tuhhthesis@authorIsMalefalse
      }{%
        \ClassError{\tuhh@ClassName}{sorry, sex must be either male or female}
      }%
    }%
  }{%
    \ClassError{\tuhh@ClassName}{sex of author can only be set in PhD mode}
  }%
}

%%%
%%% Command: \setBirthplace
%%% sets the birthplace of the author
%%%
\newcommand{\setBirthplace}[1]{%
  \ifthenelse{\equal{\tuhhthesis@type}{phd}}{%
    \def\@tuhhthesis@birthplace{#1}
  }{%
    \ClassError{\tuhh@ClassName}{birthplace of author can only be set in PhD mode}
  }%
}

%%%
%%% Command: \setPhDType
%%% sets the type of PhD: ing, nat, pol
%%%
\newcommand{\setPhDType}[1]{%
  \ifthenelse{\equal{\tuhhthesis@type}{phd}}{%
    \ifthenelse{\equal{#1}{ing}}{%
      \def\@tuhhthesis@phdType{Doktor-Ingenieur\if@tuhhthesis@authorIsMale\else in\fi~(Dr.-Ing.)}
    }{%
      \ifthenelse{\equal{#1}{nat}}{%
        \def\@tuhhthesis@phdType{Doktor\if@tuhhthesis@authorIsMale\else in\fi~der Naturwissenschaften (Dr.~rer.~nat.)}
      }{%
        \ifthenelse{\equal{#1}{pol}}{%
          \def\@tuhhthesis@phdType{Doktor\if@tuhhthesis@authorIsMale\else in\fi~der Wirtschafts- und Sozialwissenschaften (Dr.~rer.~pol.)}
        }{%
          \ClassError{\tuhh@ClassName}{PhD type must be: 'ing', 'nat', or 'pol'}
        }%
      }%
    }%
  }{%
    \ClassError{\tuhh@ClassName}{type of PhD can only be set in PhD mode}
  }%
}

%%%
%%% Commands: \supervisorFirst, \supervisorSecond
%%%
\newcommand{\supervisorFirst}[2]{%
  \@tuhhthesis@supervisorFirsttrue%
  \def\tuhhthesis@supervisorFirst@Name{#1}%
  \def\tuhhthesis@supervisorFirst@Addr{#2}%
}%
\newcommand{\supervisorSecond}[2]{%
  \@tuhhthesis@supervisorSecondtrue%
  \def\tuhhthesis@supervisorSecond@Name{#1}%
  \def\tuhhthesis@supervisorSecond@Addr{#2}%
}%

%%%
%%% Commands: \examinationChair, \examinerFirst, \examinerSecond, \examinerThird
%%%
\newcommand{\examinationChair}[2]{%
  \@tuhhthesis@examinationChairtrue%
  \def\tuhhthesis@examinationChair@Name{#1}%
  \def\tuhhthesis@examinationChair@Addr{#2}%
}%
\newcommand{\examinerFirst}[2]{%
  \@tuhhthesis@examinerFirsttrue%
  \def\tuhhthesis@examinerFirst@Name{#1}%
  \def\tuhhthesis@examinerFirst@Addr{#2}%
}%
\newcommand{\examinerSecond}[2]{%
  \@tuhhthesis@examinerSecondtrue%
  \def\tuhhthesis@examinerSecond@Name{#1}%
  \def\tuhhthesis@examinerSecond@Addr{#2}%
}%
\newcommand{\examinerThird}[2]{%
  \@tuhhthesis@examinerThirdtrue%
  \def\tuhhthesis@examinerThird@Name{#1}%
  \def\tuhhthesis@examinerThird@Addr{#2}%
}%

%%%
%%% Command: \makeStudentTitlePage
%%%
\newcommand{\makeStudentTitlePage}{%

  \begin{tikzpicture}[remember picture, overlay]
    \ifpdf% only print fancy background when in PDF mode
      \tuhhgraphics@drawTitlePageBackground
    \fi%

    %% define coordinates for the different parts of the title page
    % Subject
    \coordinate (SUBJECT) at
        ($ (current page.north) + (0, -\the\tuhhthesis@typePosY) $);
    % Title
    \coordinate (TITLE) at
        ($ (current page.north) + (0, -\the\tuhhthesis@titlePosY) $);
    % Author
    \coordinate (AUTHOR) at
        ($ (current page.north) + (0, -\the\tuhhthesis@authorPosY) $);
    % Date
    \coordinate (DATE) at
        ($ (current page.north) + (0, -\the\tuhhthesis@datePosY) $);
    % Supervisors
    \coordinate (SUPERVISOR) at
        ($ (current page.north) + (0, -\the\tuhhthesis@supervisorPosY) $);
    % Examiners
    \coordinate (EXAMINER) at
        ($ (current page.north) + (0, -\the\tuhhthesis@examinerPosY) $);

    % print title information tags
    \node[anchor=center] at (SUBJECT)    {\tuhhthesis@fnt@titlepage\usekomafont{subject}\tuhhpreamble@subject};
\if@tuhhthesis@course%
    \node[anchor=center] at ($(SUBJECT) - (0,0.8)$) {\tuhhthesis@fnt@titlepage\usekomafont{descr}\tuhhthesis@course};
\fi%
    \node[anchor=center] at ($ (SUBJECT) - (0,1.5) $) {\tuhhthesis@fnt@titlepage\usekomafont{descr}\longTUBDokNumber};
    \node[anchor=center] at (TITLE)      {\usebox{\tuhh@titleBox}};
    \node[anchor=center] at (AUTHOR)     {\tuhhthesis@fnt@titlepage\usekomafont{descr}\tuhh@printTag{AuthorBy}};
    \node[anchor=center] at ($(AUTHOR) + (0,-2\baselineskip)$) {\tuhhthesis@fnt@titlepage\usekomafont{author}\tuhhpreamble@author};
    \node[anchor=center] at (DATE)       {\tuhhthesis@fnt@titlepage\usekomafont{date}\printmonthdate};
    \node[anchor=center] at (SUPERVISOR) {\usebox{\tuhh@supervisorBox}};
    \node[anchor=center] at (EXAMINER)   {\usebox{\tuhh@examinerBox}};
  \end{tikzpicture}
}

%%%
%%% Command: \makePhDTitlePage
%%%
\newcommand{\makePhDTitlePage}{%

  \begin{tikzpicture}[remember picture, overlay]
    % the cover page is not expected to be fance; we have to obey :-(
    %\ifpdf% only print fancy background when in PDF mode
    %  \tuhhgraphics@drawTitlePageBackground
    %\fi%

    % FIXME positions should not be hard-coded! (see student title page)
    %% define coordinates for the different parts of the title page
    % Title
    \coordinate (TUBDOK) at
        ($ (current page.north) + (0, -0.14\paperheight) $);
    % Title
    \coordinate (TITLE) at
        ($ (current page.north) + (0, -0.25\paperheight) $);
    % Text
    \coordinate (TEXT) at
        ($ (current page.north) + (0, -0.47\paperheight) $);
    % Author
    \coordinate (AUTHOR) at
        ($ (current page.north) + (0, -0.59\paperheight) $);
    % Birthplace
    \coordinate (BIRTHPLACE) at
        ($ (current page.north) + (0, -0.69\paperheight) $);
    % Date
    \coordinate (DATE) at
        ($ (current page.north) + (0, -0.81\paperheight) $);
    % PhD Supervisor
    \coordinate (PHDSUPERVISOR) at
        ($ (current page.north) + (0, -0.91\paperheight) $);

    % print title information tags
    \node[anchor=center] at (TUBDOK)     {\tuhhthesis@fnt@titlepage\usekomafont{descr}\longTUBDokNumber};
    \node[anchor=center] at (TITLE)      {\usebox{\tuhh@titleBox}};
    \node[anchor=center] at (TEXT)       {\usebox{\tuhh@phdBox}};
    \node[anchor=center] at (AUTHOR)     {\tuhhthesis@fnt@titlepage\usekomafont{descr}von};
    \node[anchor=center] at ($(AUTHOR) + (0,-2\baselineskip)$) {\tuhhthesis@fnt@titlepage\usekomafont{author}\tuhhpreamble@author};
    \node[anchor=center] at (BIRTHPLACE) {\tuhhthesis@fnt@titlepage\usekomafont{descr}aus};
    \node[anchor=center] at ($(BIRTHPLACE) + (0,-2\baselineskip)$) {\tuhhthesis@fnt@titlepage\usekomafont{author}\@tuhhthesis@birthplace};
    %\node[anchor=center] at (DATE)       {\tuhhthesis@fnt@titlepage\usekomafont{date}\the\year};
    \node[anchor=center] at (DATE)       {\tuhhthesis@fnt@titlepage\usekomafont{date}\printyeardate};


    \ifthenelse{\equal{\tuhhthesis@type}{phd}}{%
      \if@tuhhthesis@approved%
      \else%
        \node[anchor=center] at (PHDSUPERVISOR) {\usebox{\tuhh@phdSupervisorBox}};
      \fi%
    }{}%
  \end{tikzpicture}
}

%%%
%%% Command: \makePhDSecondPage
%%%
\newcommand{\makePhDSecondPage}{%
  \begin{tikzpicture}[remember picture, overlay]
    % Date
    \coordinate (ANC) at
        ($ (current page.north) + (0, -0.8\paperheight) $);
%
%    % content
    \node[anchor=south] at (ANC)   {\usebox{\tuhh@phdExaminationBox}};
  \end{tikzpicture}
}

%%%
%%% create idx file if index is turned on
%%%
\if@tuhhthesis@index%
  \makeindex%
\fi%

%%%
%%% Command: \printTUHHIndex
%%% only available if index is turned on
\newcommand{\printTUHHIndex}{%
  \if@tuhhthesis@index%
    {\scriptsize \printindex}
  \else
    \ClassError{\tuhh@ClassName}{Command 'printTUHHIndex' is only available if index is turned on.}
  \fi%
}%

\makeatother
\endinput
