# DynamicInstructionScheduling

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li>
	<a href="#usage">Usage</a>
    	<ul>
		<li><a href="#input-format">Input Format</a></li>
		<li><a href="#clean-project">Clean Project</a></li>
	</ul>
    </li>
    <li>
      <a href="#testing-on-eustis-3">Testing on Eustis 3</a>
    </li>
    <li><a href="#license">License</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

# About the Project

# Getting Started

To get started you must have `g++` installed to run this program.

To install the G++ compiler on Linux run:

```bash
sudo apt install g++
```

Verify that you have `g++`:

```
g++ --version
```

The `Makefile` also runs memory leak detection using `valgrind`. To install valgrind:

```
sudo apt install valgrind
```

# Usage

To compile the program run:

```bash
make
```

## Input Format

## Clean Project

After running `make` and `./sim`, clean the project:

```bash
make clean
```

To force clean, run:

```bash
make clobber
```

# Testing on Eustis 3

To connect to eustis 3:

```bash
ssh YOUR_NID@eustis3.eecs.ucf.edu
```

Enter your NID password and then run:

```bash
cd DynamicInstructionScheduling/
make
./sim [with parameters]
```

## Getting Project Folder

Before logging into eustis 3, transfer the project folder:

```bash
scp -r DynamicInstructionScheduling/ YOUR_NID@eustis3.eecs.ucf.edu:~/
```

Then, enter you credentials.

OR

Clone the project from GitHub:

```bash
git clone https://github.com/stefanwerleman/DynamicInstructionScheduling.git

cd DynamicInstructionScheduling/
```

# License

Distributed under the MIT License. See `LICENSE` for more information.

# Acknowledgments

-   [The Pitchfork Layout](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs)

-   **spdlog: C++ Logger**
    -   [Home Page](https://spdlog.docsforge.com/master/)
    -   [GitHub](https://github.com/gabime/spdlog)
