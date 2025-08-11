# CopyGnome
A small command line program for automated file copying with integrated exclusion list functionality.

## Features
- Automated recursive copying of files from one location to another.
- Powerful file exclusion feature that allows to fine-tune which files from which directory will be copied.

## Usage
1. Build the project.
2. Launch the `CopyGnome.exe` file.
3. The program will ask to provide the paths to source and destination directories.
   - The specified directories must exist.
   - The provided paths can be either relative or absolute.
4. The program will copy all specified files and directories and terminate.
   - All directories will be copied recursively.
   - In each directory it will look for a `.gnomeIgnore` file.
   - The patterns in the `.gnomeIgnore` file will be added to the exclusion list.
   - The patterns specified in the `.gnomeIgnore` file only apply to the directory it is present in and its subdirectories.

### Usage of .gnomeIgnore
Files named `.gnomeIgnore` allow the user to specify which files and directories should be ignored while copying (similar to how `.gitignore` works).

#### Rules:
- Each line can hold up to 1 pattern.
- Lines starting with `#` will be ignored. Empty lines will also be ignored.
- Whitespace characters at the start and end of the line will be removed.
- The pattern rules are based on standard C++ flavour regex with some additional caveats:
  - All the `.` and `^` characters in the pattern will be automatically escaped using `\` symbol.
  - All `*` characters will have `.` prepended in front of them. In short, all `*` symbols will be treated as completely arbitrary string.
  - All `/` and `\` characters will be changed to `/` and automatically escaped using `\` symbol.
  - Patterns ending with `/` or `\` will only exclude directories.
  - Patterns ending with `$` will only exclude files.
- The patterns specified in the `.gnomeIgnore` file only apply to the directory it is present in and its subdirectories. It means that:
  - The scope of `.gnomeIgnore` file is limited to the directory it is located in and it does not affect its parent or sibling directories.
  - The parts of the path preceding the directory that contains the `.gnomeIgnore` file will not be checked for matches to the patterns inside that `.gnomeIgnore` file.
- Source directory may contain multiple `.gnomeIgnore` files in it and its subdirectories.

### Optional command line arguments
- -s \<source folder path\> – specify the source directory from which the files will be copied. The program will not ask for source path later.
- -d \<desstination folder path\> – specify the destination directory to which the files will be copied. The program will not ask for destination path later.
