# Text Adventure in C

## Intro

This started off as a way of learning C, but has evolved into a parser / interpreter project in an attempt to do something more interesting with the concept.

I've always had an interest in text adventures; in fact I learned to program in JavaScript back in the early 2000s by programming simple text adventures in a Delphi-based editor.

As an avid reader of fantasy, and later 'serious', literature there's something viscerally appealing about text adventures; they're stripped-back, minimal versions of games. Similar to how C is a stripped-back, minimal programming language.

## Design Philosophy

In designing this engine I wanted to make something clean and reasonably easy to understand with a little digging. It's inspired by a variety of projects, notably the now-defunct Legendary Tales engine and the Inform engine, but aims to be a fun project from the programming side rather than focusing purely on the user experience.

One key idea behind the design of the project is the separation of interface and data. This is common in graphical projects, but easy to let slip in text-based ones.

The reason for this is that it lets a variety of interfaces from clickable menus to exotic console variations use the parser at the engine's core without incident. At some point in the future I would love to add a graphical interface for developing stories on this engine.

## The Parser

### Grammar

At the moment the grammar of the parser is very simple. It accepts two forms:

* *[verb]*
* *[verb] [noun]*

The noun can be multiple words long; the lexer tests against known words (presently implemented as a Binary Search Tree) so the mere presence of a space character will not throw off interpretation.

### Technical workings

The gamedata object contains all other objects in the game.

It has a list of gameobjs, which are interacted with via the word tree. When a player types a command, the parser determines what each of the words means using the word tree (translating it into parsetokens at first, then verbs/nouns).
