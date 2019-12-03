# Advent of Code 2019, ReasonML

Doing [Advent of Code 2019](https://adventofcode.com/2019):

* Using [ReasonML](https://reasonml.github.io/) (an alternate syntax for OCaml)
* Using [Bucklescript](https://bucklescript.github.io/) to compile to Javascript
* Using [Tablecloth](https://github.com/darklang/tablecloth) as a standard library

Solutions in the `/src` directory.

There's not a great reason to compile to Javascript for these challenges but I'm curious to explore the toolchain. Might switch to compiling to native code at some point.

# Build
```
npm run build
```

# Build + Watch

```
npm run start
```

# Run a solution

```
node src/day1/solution.bs.js
```
