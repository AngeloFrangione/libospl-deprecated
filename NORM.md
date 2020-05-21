# Our c norm;
--------------------------------------------------

This norm aims to make a code that is coherent and readable to other contributors.  
You should follow these rules as much as you can.  
Not following formatting rules will likely make your pull request rejected.  
Doing forbidden things will make us reject your pull request.  
If you have any question or remark about this norm, open an issue. We will read it carefully.

## Part 1: naming
Naming variables, functions names and other stuff like file names must follow these guidelines:

* Names must be clear and in english and as explicit as possible (except for counters)
* Counters with explicit names are appreciated (l for line counter, c for column counter, ...)
* Only lower case ascii characters allowed
* Words must be separated with underscore '\_' (ex: `my_var`)
* Some data structures must be prefixed like this :

|data structure|prefix|
|--------------|---|
|structure     |s_ |
|typedef       |t_ |
|union         |u_ |
|enum          |e_ |

* You can use shortcuts for the names if they are explicit enough (like `nb_thing` but not `nb_thg`)
* Every declaration of a variable must be used

## Part 2: formatting{}
The code itself should respect a few things:

* You must indent the code with tabulations with a size of _4_. ___tabulations___ not _spaces_.
* Try to avoid making functions over 30-35 lines. Try to _split_ the code **as most as you can**. Avoid making functions that can be done ___reéusable___.
* Try to avoid writing lines that are larger than 100 columns. Do not forget that tabulations are 4 columns large.
* Try to get the smallest form of your conditions. Smaller conditions are often easier to understand and optimized.
* Only one instruction per line.
* An empty line is an _empty_ line. No spaces, no tabulations. Empty.
* Declaring variable on the top of the function is often clearer but not mandatory.
* Try to space out your code sensibly. Avoid using more than one empty line.
* The end of a line should be empty. _Empty_ like empty lines.
* You must put the curly braces at the next line:

```C
// this is NOT right
int main(void) {
	return 0;
}

// this is right
int main(void)
{
	return 0;
}

```

## Part 3: functions()

* Avoid to put more than 4 parameters in a function.  
  If your function needs more than 4 parameters then it probably can be split  
  or you probably can create data structures handling some of thoses parameters.
* A function that returns nothing should be prototyped with void as argument.
* For spacing-out reason please add a single empty line after each function:

```C
// This is NOT right
int my_function(void)
{
	return 1;
}
int my_second(void)
{
	return 2;
}

// This is right
int my_function(void)
{
	return 1;
}

int my_second(void)
{
	return 2;
}

```
* Try to make a little comment over each function to explain it (if it's not clear enough)
* You can also add what parameters it takes and what it returns
* We use Doxygen for generating a html documentation so please use the doxygen format.

```C
/**
 * \brief Returns the parameter
 *
 *  This function returns the integer given as first parameter
 * \param param1 An integer that will be returned
 */
 
int my_superb_function(int param1)
{
	return param1;
}
```

## Part 4: files.c

* File names must be explicit about what they contain.  
  If it contains only a struct definition, it should have the struct name as its own name.
  If it conatins only one function, it should have the function name as its own name.
* A file should never contain functions that are not related one to each other.
* Use static keyword when a function is reachable only in the file where it is defined.
* Please write the short licence at the top of the file

## Part 5: header.h

* Protect it against double inclusion.
  If the file is named name.h you should `#define NAME_H`
* These definitions must be in header files
  * Function prototypes
  * Structure, union and enum
  * Typedefs
* Defines are in uppercase (ex: `#define RED_COLOR \033[0;31m`)
* Please write the short licence at the top of the file

## Part 6: things that aren't allowed

* Variable length array (VLA)
* Typedefs for pointers (or arrays)
```C
typedef t_matrix *t_matrix_ptr;
// allows to declare t_matrix *m as t_matrix_ptr m
// forbidden
```

## Example

```C
/*	libospl - Open Source Photo Library
	an opensource and multiplateform photo library management that can be used
	to store and sort all your pictures.
	Copyright (C) 2019-2020 Angelo Frangione

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/**
 * \file matrix.h
 * \brief This file contains matrix related functions
 * \author Angelo Frangione & Edgar Fouillet
 *
 * All the matrix related functions are in this file 
 */
 
//Header file
#ifndef MATRIX_H
#define MATRIX_H

typedef struct s_matrix
{
	float **matrix;
	int   lines;
	int   columns;
} t_matrix;

t_matrix *matrix_alloc(int lines, int columns);
t_matrix *matrix_multiplication(t_matrix *m, float k);

#endif // MATRIX_H

//Source file
#include "matrix.h"

/**
 * \brief Multiply a matrix
 * Gives the product of matrix a by a scalar k
 * \param m a matrix
 * \param k the scalar to multiply a with
 * \return the product of m by k
 */

t_matrix *matrix_multiplication(t_matrix *m, int k)
{
	t_matrix *ret;
	
	if (!(ret = matrix_alloc(ret->lines, ret->columns)))
		return NULL;

	for (int l = 0; l < m->lines; l++)
	{
		for (int c = 0; c < m->columns; c++)
		{
			ret->matrix[l][c] = k * m->matrix[l][c];
		}
	}

	return ret;
}
```
