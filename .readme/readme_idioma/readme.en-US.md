<p align="center">
    <a href="https://github.com/lenguaje-latino">
        <img width="90%" align="center" src ="https://raw.githubusercontent.com/MelvinG24/Latino/master/.readme/imgs/banner-300x.png" />
    </a>
</p>

<div align="center">

![GitHub release (latest by date)](https://img.shields.io/github/v/release/Lenguaje-Latino/Latino)
[![https://t.me/joinchat/EBHu7z6l6_paWtcJgu9DVQ](https://img.shields.io/badge/Soporte-Telegram-green.svg)](https://t.me/joinchat/AAAAAD6l6_qIgQAAgu9DVQ)
[![Join the chat at https://gitter.im/primitivorm/latino](https://badges.gitter.im/primitivorm/latino.svg)](https://gitter.im/primitivorm/latino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[![Build Status](https://travis-ci.org/primitivorm/latino.svg?branch=master)](https://travis-ci.org/primitivorm/latino)
<a href="http://lenguaje-latino.org"><img src="https://img.shields.io/npm/l/vue.svg" alt="License"></a>
[![codecov.io](http://codecov.io/github/primitivorm/latino/coverage.svg?branch=master)](http://codecov.io/github/primitivorm/latino?branch=master)

| README  | [Español](../../README.md) | [Français](readme.fr-FR.md) | [Português](readme.pr-BR.md) | [Italiano](readme.it-IT.md) |
|---|---|---|---|---|

</div>

<a name="table"> </a>
# Table of Contents
* [Table of contents](#table)
    * [What is Latino?](#whatIs)
        * [Introductory video](#intro)
    * [Why use Latino?](#Why)
    * [Install Latino](#inst)
    * [Documentation](#doc)
    * [Latino-Wiki](#wiKi)
    * [Other Help](#help)
    * [Contributions](#contri)
    * [LATINO SYNTAX](#syntx)
        * [Comments](#comt)
        * [Variables](#var)
            * [An identifier can](#can)
            * [An identifier CANNOT](#CANNOT)
        * [Constants](#const)
        * [Data types](#data)
        * [Operators](#opds)
        * [Control structure](#estrCtrl)
            * [yes (if)](#yes)
            * [choose (switch case)](#choose)
            * [from (for loop)](#from)
            * [while (do while)](#while)
            * [repeat-until (repeat)](#rept)
        * [Functions](#fun)
        * [List](#list)
        * [Dictionaries](#dec)
        * [Reserved words](#plbrsRvds)
    * [License](#lic)

<a name="whatIs"> </a>
# What is Latino?
* Latino * is a programming language with syntax in Spanish created in [C] (https://es.wikipedia.org/wiki/C_ (lengua_de_programaci% C3% B3n)), inspired by [Lua] (https: // www.lua.org/) and [Python] (https://www.python.org). This project was born from the need to increase basic and advanced level education, so that children, adolescents and adults are motivated to enter the world of programming and develop applications in a syntax in their language. Furthermore, * Latino * is also for developers who would like to program in Spanish, since * Latino * is fully functional in any [API] (https://es.m.wikipedia.org/wiki/Interfaz_de_programaci%C3%B3n_de_aplicaciones) in raw.

<a name="intro"> </a>
### Introductory Latino Video (click on the image)
[! [Introductory Latino Video] (https://j.gifs.com/GvrEK0.gif)] (https://www.youtube.com/watch?v=LzA5FRt8Oqo)

<a name="porQue"> </a>
# Why use Latino?
* Latino *, being a programming language with syntax in Spanish, provides us with certain advantages when programming in it.
1. ** Intuitive **:
    > Its syntax in Spanish makes it easier to understand the code, thus reducing learning time when programming.
2. ** Easy **:
    > * Latino * has a clean syntax and does not require the use of a semicolon (`;`) at the end of each code as in the case of Java, Javascript, C / C ++, among others.
3. ** High-level language **:
    > This means that it is a language that resembles the grammar we use to read and write. However, [low-level languages] (https://es.wikipedia.org/wiki/Lenguaje_de_bajo_nivel) are those that the machine understands, such as [binary code] (https://es.wikipedia.org/wiki / Lenguaje_de_m% C3% A1quina) or the [Assembly Language] (https://es.wikipedia.org/wiki/Lenguaje_ensamblador).
4. ** Portable **:
    > When you write your code in * Latino * it can be executed on any other platform easily and safely, unlike other programming languages ​​such as [Visual Basic] (https://es.wikipedia.org/wiki / Visual_Basic) that only works on MS-Windows platforms.
5. ** Open source **:
    > Anyone can download * Latino * source code, modify it, extend its libraries and contribute to its development if they wish.

---

! [Captura_de_Pantalla-Latino] (https://raw.githubusercontent.com/MelvinG24/Latino/master/.readme/imgs/latino_sublime.png)

<a name="inst"> </a>
# Install Latino
- [Windows] (. Readme / OS_install / installation_windows.md)
- [Debian / Ubuntu] (. Readme / OS_install /instacion_debian.md)
- [Fedora] (. Readme / OS_install / instacion_fedora.md)
- [Mac] (. Readme / OS_install / instacion_mac.md)
- [Plugins] (https://github.com/latino-language)

<a name="doc"> </a>
# Documentation
Learn about this programming language by visiting its official documentation at the following link.
- [Manual Latino] (https://manual-latino.readthedocs.io/es/latest/)

<a name="wiKi"> </a>
# Latino-Wiki
Visit the Latino Wiki here on GitHut to learn how to collaborate on this project and to learn how to compile Latino on each operating system.
- [Latino-Wiki] (https://github.com/MelvinG24/Latino/wiki)

<a name="help"> </a>
# Other Help
* Latino * has a forum on its official website, as well as a group on Telegram and Gitter, as well as a YouTube channel that you can contact if you have any questions.
- [Stack Overflow] (https://es.stackoverflow.com/questions/tagged/latino)
- [Chat on Telegram] (https://t.me/joinchat/AAAAAD6l6_qIgQAAgu9DVQ)
- [Chat in Gitter] (https://gitter.im/primitivorm/latino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
- [Channel on Youtube] (https://www.youtube.com/channel/UCLVTJpQn-TDbBSwR732kvnQ/featured)
<! - - [Latino API] (https://manuallatinoapi.blogspot.com) ->

<a name="contri"> </a>
# Contributions
If you want to contribute to this project by reporting errors, proposing suggestions or contributing to the source code, we leave you the following link with our rules.
- [Rules for taxpayers] (. Readme / CONTRIBUTING.md)

<a name="sintx"> </a>
# LATINO SYNTAX
The definition of the * Latino * programming language is explained in a general way below.
<a name="comt"> </a>
## I. Comments:
Single line comments will start with the cat sign `#` (as in python) or `//` (as in C).
```js
#This is a python style comment
// This is a C-style comment
```
Multi-line comments are C-style. They start with `/ *` and end with `* /`.
```c
/ *
This is a
commentary
multiline
* /
```
<a name="var"> </a>
## II. Variables:
Variables are identifiers associated with values.
python
name = "Juan Perez"
grade = 10
numbers = [1, 2, 3, 4, 5] // this is a list or array.
salaries = {"Jesus": 10000, "Maria": 20000, "Jose": 30000} // this is a dictionary
`` ''

It is possible to assign more than one variable in a single line of code
python
a, b, c = 1, 2, 3 #a = 1 b = 2 c = 3
a, b, c = 1, 2 #a = 1 b = 2 c = null
a, b = 1, 2, 3 #a = 1 b = 2 the value 3 is discarded
`` ''
<a name="can"> </a>
### __ An identifier can: __
1. Start with underscore `_` or letters` a-z or A-Z`. Accented letters and `ñ` are not valid as letters in identifiers.
2. Contain uppercase and lowercase characters.
Latino is case sensitive. So the following identifiers are not the same.
python
message = "Hello world"
Message = "Goodbye baby!"
`` ''
<a name="Cannot"> </a>
### __An identifier CANNOT: __
1. Start with a number.
2. Start with a symbol, or even if it is a reserved word.

<a name="const"> </a>
## III. Constants:
When a constant is declared, the value must also be forcibly assigned.

Constants must be declared in ** uppercase **.
python
PI = 3.14159
G = 9.8
`` ''

<a name="data"> </a>
## IV. Type of data
| latin | data type in C |
| --- |: ---: |
| logical | ** bool ** |
| numerical | ** double ** |
| string or literal | ** `char *` ** |
| list (arrangement) | ** struct ** |
| dictionary | ** struct ** |

<a name="opds"> </a>
## V. Operators:
The operators are listed below:
| Category | Operators |
| --- | --- |
| Arithmetic | `+, -, *, /,% (modulo), ^ (power)` |
| Logical | && (and), & # 124; & # 124; (or) |
| Concatenation | `..` |
| Increase, decrease | `++, --` (valid only in post) |
| Relational | `==,! =, <,>, <=,> =, ~ = (regex)` |
| Assignment | `=` |
| Member login | `.` |
| Ternary operator | `(condition)? option1: option2` |

Operator precedence is the same as other programming languages ​​like C / Python / Lua.

The ternary operator can be used to assign values ​​based on a condition, the parentheses are required to obtain the expected result.
python
number = -5
message = (number <0)? "is negative": "is positive"
write ("The number" .. number .. message)
#output: The number -5 is negative
`` ''
<a name="estrCtrl"> </a>
## SAW. Control structures:
<a name="yes"> </a>
### yes (if)
Evaluate a condition and if the result is `true` execute
instructions below. The parentheses are optional in the condition.
python
yes (condition)
   #code
finish

age = 18
if age> = 18
    write ("You are of legal age, you can vote now.")
finish
#exit: You are of legal age, you can vote now.
`` ''

In case the result of the condition is `false`, the code must be executed after the reserved word` but`.
python
yes condition
   #code
otherwise
   #code
finish

age = 5
if age> = 18
    write ("You are of legal age, you can vote now.")
otherwise
    write ("You are a boy, you have to go to school.")
finish
#exit: You are a child, you have to go to school.
`` ''

It is possible to nest the `if-but` statements as follows:
python
yes condition
   #code
otherwise
    yes condition
        #code
    otherwise
        #code
    finish
finish
`` ''
There is a more elegant way to write the above code with the `osi` keyword. In python it is `elif expression:`.
python
yes condition1
    #code
osi condition2
    #code
osi condition3
    #code
otherwise
    #code
finish
`` ''

---

<a name="choose"> </a>
### choose (switch case)
Evaluate one option from multiple possible cases.
The option can be an expression, in case no option is fulfilled in any case, the code is executed after the reserved word `other` or` default`.
Case values ​​can only be numeric or strings.
python
choose (option)
    case value1:
        #code
    case value2:
        #code
    case value3:
        #code
    default:
        #code
finish

grade = 'B'
choose (rating)
    case 'A':
        write ("Excellent !.")
    case 'B':
        write ("Well done !.")
    case 'C':
        write ("Well done !.")
    case 'D':
        write ("You still raisin.")
    case 'F':
        write ("You are failed.")
    other:
        write ("Invalid grade.")
finish
#output: Well done!
`` ''
Note that the case has to be repeated for `B` and` C` at the moment multiple cases are not allowed as a single option.

---

<a name="from"> </a>
### from (for loop)
Makes an instruction or instruction block repeat
from an initial condition and while the condition is fulfilled (that is, it is `true`), in this sentence the parentheses are required.
python
from (start_condition; condition; increment)
     #code
finish

since (i = 0; i <= 10; i ++)
     write (i)
finish
#output: 0 1 2 3 4 5 6 7 8 9 10

since (i = 10; i> = 0; i--)
     write (i)
finish
#output: 10 9 8 7 6 5 4 3 2 1 0
`` ''

A different jump can be specified by changing the increment expression.
python
since (i = 0; i <50; i = i + 10)
    print (i)
finish
#departure: 0 10 20 30 40
`` ''

---

<a name="while"> </a>
### while (do while)
Makes an instruction or instruction block repeat
As long as the condition is `true`, the parentheses are optional in the condition.
python
while (condition)
    #code
finish

i = 0
while i <10
    write (i)
    i ++ #increment
finish
#output: 0 1 2 3 4 5 6 7 8 9
`` ''

---

<a name="rept"> </a>
### repeat-up (similar to Lua's `repeat`)
Makes an instruction or instruction block
are repeated while the condition is `false`,
the code statements are executed at least once.
The parentheses are optional in the condition.
python
repeat
    #code
until condition

i = 0
repeat
    write (i)
    i ++ #increment
up to i == 10
#output: 0 1 2 3 4 5 6 7 8 9
`` ''

Loops (`from`,` while` and `repeat`) can be exited with the` break` keyword.
python
since (i = 0; i <10; i ++)
    if (i == 5)
        break #exits the cycle from
    finish
    print (i)
finish
#output: 0 1 2 3 4 #prints only up to 4
`` ''
<a name="fun"> </a>
## VII. Features
A function generally consists of a list of statements to be executed, a list of input parameters that will regulate said action.

Functions are defined with the keyword `function` or the short form` fun`.

You can return the value with the keyword `return`,` return` or the short form `ret`.
The structure of a function is as follows:
python
function functionName (argument1, argument2)
    #code
    return result
finish

#The following function adds two numbers
fun add (a, b)
  ret a + b
finish
`` ''

To invoke (execute) a function is done with the name of the function and the list of parameters in parentheses.
python
r = add (2, 3) # the result is stored in the variable r
write (r)
#output: 5
`` ''

You can create functions with a variable number of arguments with `...` in the last parameter of the definition.
python
function varArgs (arg1, arg2, ...)
  va = [...] #parameters 3 onwards are obtained as a list and assigned to the variable va
  write ("parameter 1:" .. arg1) #prints parameter 1
  write ("parameter 2:" .. arg2) #prints parameter 2
  write ("parameter 3:" .. goes [0]) #prints parameter 3
  return arg1 + arg2
finish

#varArgs function call with 2 elements
r = varArgs (1, 2)
write (r)
#exit:
parameter 1: 1
parameter 2: 2
parameter 3: null
3

#call to varArgs function with 3 elements
r = varArgs (1, 2, 3)
write (r)
#exit:
parameter 1: 1
parameter 2: 2
parameter 3: 3
3
`` ''
<a name="list"> </a>
## VIII. Lists
A list is a type of collection. It is equivalent to what is known in other languages ​​as arrays or vectors.

Lists can contain any type of data: logical, numeric, literal, string, lists, dictionaries.

Creating a list is as simple as indicating the values ​​we want to include in the list in brackets and separated by commas.
python
#declaration of lists
numbers = [1, 2, 3, 4, 5]
empty = []
`` ''

We can access each of the elements of the list by writing the name of the list and indicating the index of the element between brackets `[]`.
Note that the index of the first item in the list is 0:
python
write (numbers [1])
#output: 2
`` ''

We can also use this operator to modify an element of the list if
we put on the left part of an assignment:
python
numbers [0] = 99
write (numbers)
#output: [99, 2, 3, 4, 5]
`` ''

We can also use negative numbers. If a negative number is used as an index, this means that the index starts counting from the end, to the left; that is, with [-1] we would access the last element of the list, with [-2] the penultimate, with [-3], the penultimate, and so on.
python
write (numbers [-1])
#output: 5
`` ''
<a name="dic"> </a>
## IX. Dictionaries
Dictionaries, also called associative arrays, owe their name to the fact that they are collections that relate a key and a value, between braces and separating the value of the key with a colon.
python
#Dictionary of characters and actors:
actors = {"Chilindrina": "Maria Antonieta de las Nieves",
     "El chavo del 8": "Roberto Gomez Bolaños",
     "Three skates": "Leopoldo Fernandez"}
`` ''

The first value is the key and the second is the value associated with the key.

As a key we use strings, this is so because dictionaries are implemented as hash tables, and when entering a new key-value pair in the dictionary, the hash of the key is calculated so that later the corresponding entry can be found quickly.

If the key object were modified after it was entered in the dictionary, obviously,
its hash would also change and could not be found.

The main difference between dictionaries and lists is that the values ​​stored in a dictionary are accessed not by their index, because in fact they have no order, but by their key, using brackets `[]`.
python
write (actors ["Chilindrina"])
#departure: Maria Antonieta de las Nieves
`` ''

As in lists, you can also use square brackets to reassign values.
python
actors ["Chilindrina"] = "Maria Antonieta"
write (actors ["Chilindrina"])
#departure: Maria Antonieta
`` ''
<a name="plbrsRvds"> </a>
## X. Words reserved so far
`` ''
case
true | true
continue
default | other
since
choose
fake
finish
function | fun
global
until
while
null
for
repeat
return | return | ret
break
Yes
otherwise
or if
`` ''
<a name="lic"> </a>
# License
Licensed under the [MIT] license (https://github.com/MelvinG24/Latino/blob/master/LICENSE.txt) <br/>
Any contribution or suggestion is welcome.