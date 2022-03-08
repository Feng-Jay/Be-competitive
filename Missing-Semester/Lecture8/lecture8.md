# Metaprogramming

## Build System

`Make` is one of the most common build systems. When run `make`, it will consult a file named `Makefile` in the current directory:

```makefile
paper.pdf: paper.tex plot-data.png
	pdflatex paper.tex

plot-%.png: %.dat plot.py
	./plot.py -i $*.dat -o $@
```

The things named in the r-hand are dependencies, and the l-hand are targets. In `make`, the first directive defines the default goal. You can pass paramesters to `make` to change goal, like `make plot-%.png`.

`%` is a `pattern`, it will match the same string on the left and right. 

`make` will check all the previous targets to see if they still up-to-date. If it is, it will not be reproduced.

## Dependency management

These days, most dependencies will be available through a repository that hosts a large number of such dependencies in a single place, and provides a convenient mechanism for installing them. 

**Here are some terminology they use.**

1. versioning

Most projects rely on issuing `version number` to verify different releases. Its most important purpose is keep softwares working. There are many meanings of version number, but one relatively common standard is `semantic versioning`:

**Every version number is constituded of: major.minor.patch**

- If a new release does not change the API, increase the patch version.

- If you add to your API in a backwards-compatible way, increase the minor version.

- If you change the API in a non-backwards-compatible way, increase the major version.


2. Lock files

A lock file is simply a file that lists the exact version you are currently depending on of each dependency. Usually, you need to explicitly run an update program to upgrade newer version of your dependencies.

## Continuous integration systems

Continuous integration, or CI, is an umbrella term for “stuff that runs whenever your code changes”. For example: Github Action. They all work in roughly the same way: 

Add a file to your repository that describes what should happen when various things happen to that repository. 

By far the most common one is a rule like “when someone pushes code, run the test suite”. When the event triggers, the CI provider spins up a virtual machines (or more), runs the commands in your “recipe”, and then usually notes down the results somewhere.  

## Brief aside on testing

- Test suite: a collective term for all the tests.

- Unit test: a "micro-test" that tests a specific feature in isolation.

- Intergration test: a “macro-test” that runs a larger part of the system to check that different feature or components work together.

- Regression test: a test that implements a particular pattern that previously caused a bug to ensure that the bug does not resurface.

- Mocking: to replace a function, module, or type with a fake implementation to avoid testing unrelated functionality. For example, you might “mock the network” or “mock the disk”.

## Exercises

1. 

```makefile
paper.pdf: paper.tex plot-data.png
	pdflatex paper.tex 

plot-%.png: %.dat plot.py
	./plot.py -i $*.dat -o $@
.PHONY: clean
clean: 
	git ls-files -o | xargs rm -f
```

3. 

```makefile
/Users/ffengjay/Be-competitive/Missing-Semester
```

4. 

You can visit my `Github Pages` by [access](www.ffhw.site).

And the `shellcheck` action can be done this [way](https://github.com/marketplace/actions/shellcheck).

5. 

I added an readme `Github Action`. 




