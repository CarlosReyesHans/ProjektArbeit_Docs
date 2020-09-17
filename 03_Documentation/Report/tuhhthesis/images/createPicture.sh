#!/bin/sh

progName=`basename $0`

if [ $# != 1 ]
then
    echo "usage: $progName <TikZ file>"
    exit 1
fi

tikzSuffix=".tikz.tex"
tikzFile="$1"
baseFile=`basename $1 $tikzSuffix`

if [ "$baseFile" = "$1" ]
then
    echo "$progName: TikZ file must have '"$tikzSuffix"' suffix"
    exit 2
fi

echo "using TikZ file: $tikzFile"

cat > $baseFile.tex << EOF
\documentclass[10pt,a4paper,parskip]{scrbook}
\usepackage[T1]{fontenc}
\usepackage{textcomp}
\usepackage[scaled=.92]{helvet}
\usepackage{courier}
\usepackage{amsmath}
\usepackage{amssymb}
%\usepackage{mathabx}% for circles in tables
\usepackage{pifont}
%\usepackage[varg]{txfonts}
\usepackage{tikz}
\usetikzlibrary{shapes,shadows,arrows,patterns,trees,automata,positioning,snakes}
\usetikzlibrary{decorations.text}
\usetikzlibrary{decorations.fractals}
\usetikzlibrary{decorations.markings}
\usetikzlibrary{decorations.pathmorphing}
\usetikzlibrary{decorations.text}
\usetikzlibrary{decorations.footprints}
\usetikzlibrary{decorations.pathreplacing}
\usetikzlibrary{decorations.shapes}

\usepackage[active,tightpage]{preview}
\PreviewEnvironment{tikzpicture}


\pagestyle{empty}
\begin{document}

\include{setup_math}

%\tikzstyle{every node}=[font=\large]
\tikzstyle{graphnode}=[fill=black!20,circle,inner sep=5pt,draw]
\tikzstyle{emptynode}=[fill=white,circle,inner sep=5pt,draw]
\tikzstyle{sinknode}=[style=graphnode,fill=black!60]
\tikzstyle{descnode}=[draw,rounded corners,node distance=1.7cm,inner sep=7pt,text width=4em,text centered]
\tikzstyle{lowdescnode}=[style=descnode,node distance=1.1cm]
\tikzstyle{level 1}=[level distance=3cm,sibling distance=8cm]
\tikzstyle{level 2}=[level distance=3cm,sibling distance=5cm]
\tikzstyle{level 3}=[level distance=3cm,sibling distance=3cm]


\input{$baseFile.tikz.tex}

\end{document}

EOF

pdflatex $baseFile.tex

\rm -f $baseFile.tex
\rm -f $baseFile.aux
\rm -f $baseFile.log
\rm -f $baseFile.out

exit 0

