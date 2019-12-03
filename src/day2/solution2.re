open Tablecloth

let input = "1,12,2,3,1,1,2,3,1,3,4,3,1,5,0,3,2,9,1,19,1,19,6,23,2,6,23,27,2,27,9,31,1,5,31,35,1,35,10,39,2,39,9,43,1,5,43,47,2,47,10,51,1,51,6,55,1,5,55,59,2,6,59,63,2,63,6,67,1,5,67,71,1,71,9,75,2,75,10,79,1,79,5,83,1,10,83,87,1,5,87,91,2,13,91,95,1,95,10,99,2,99,13,103,1,103,5,107,1,107,13,111,2,111,9,115,1,6,115,119,2,119,6,123,1,123,6,127,1,127,9,131,1,6,131,135,1,135,2,139,1,139,10,0,99,2,0,14,0";
let testInput = "1,1,1,4,99,5,6,0,99";
let goal = 19690720;

let parse = (str) : array(int) => {
  String.split(str, ~on=",")
    // TODO: Weird to default to 0 here. Would be better to raise an exception
    -> List.map(~f= (str) => Result.withDefault(String.to_int(str), ~default=0))
    -> Array.from_list
};

// Not strictly necessary but might as well have fun with sum types
type op = Add | Multiply | Halt;

exception UnknownOpcode;
exception MissingValue;
exception BadProgram;

let intToOpcode = (int) => {
  switch(int) {
    | 1 => Add
    | 2 => Multiply
    | 99 => Halt
    | _ => raise(UnknownOpcode)
  }
};

// Get a value in an array, given an indirect index
let getPointer = (array, index) => {
  let result = Array.get(array, ~index = index) -> Option.andThen(~f = (i) => Array.get(array, ~index = i));
  switch(result) {
    | Some(res) => res
    | None => raise(BadProgram)
  }
};

// Set a value in an array, given an indirect index. 
// Return the mutated array
let setPointer = (array, index, value) => {
  let idxToSet = switch(Array.get(array, ~index = index)) {
    | Some(i) => i
    | None => raise(BadProgram)
  };

  Array.set(array, ~index = idxToSet, ~value = value);
  array
};

// Execute add, return modified memory
let add = (program, ~index) => {
  let num1 = getPointer(program, index + 1);
  let num2 = getPointer(program, index + 2)
  setPointer(program, index + 3, num1 + num2)
}

// Execute multiply, return modified memory
let multiply = (program, ~index) => {
  let num1 = getPointer(program, index + 1);
  let num2 = getPointer(program, index + 2)
  setPointer(program, index + 3, num1 * num2)
}

let rec interpret = (program, ~index) => {
  let value = Array.get(program, ~index = index);
  let opcode = switch (value) {
    | Some(int) => intToOpcode(int)
    | None => raise(MissingValue)
  };

  let newProgram = switch(opcode) {
    | Halt => program
    | Add => add(program, ~index = index)
    | Multiply => multiply(program, ~index = index)
  };

  switch(opcode) {
    | Halt => program
    | _ => interpret(newProgram, ~index = index + 4)
  }
};

// Convert an option to a value, or raise
let getExn = (option) => {
  switch(option) {
    | Some(res) => res
    | None => raise(MissingValue)
  };
}

let run = (input) : int => {
  interpret(input, ~index=0) -> Array.get(~index = 0) -> getExn
}

// part 1

let program = parse(input);
Js.log(run(program));


// part 2

let runWithInputs = (noun: int, verb: int) => {
  let program = parse(input);
  Array.set(program, ~index=1, ~value=noun);
  Array.set(program, ~index=2, ~value=verb);
  run(program)
};

let range = (max) => List.initialize(max, (n) => n + 1);

let rec findSolution = (noun, verb) => {
  let result = runWithInputs(noun, verb);
  if (result == goal) {
    (noun, verb)
  } else {
    if (verb < 100) {
      findSolution(noun, verb + 1)
    }
    else {
      findSolution(noun + 1, 0)
    }
  }
}

Js.log(findSolution(0, 0));


