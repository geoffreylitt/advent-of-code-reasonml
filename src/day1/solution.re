open Tablecloth

// part 1

let fuelForMass = (mass) => (mass / 3) - 2

let fuelForMassStr = (massStr) => {
  let mass = String.toInt(massStr);
  switch(mass) {
    | Ok(m) => fuelForMass(m)
    | Error(_) => 0
  }
};

let part1 =
  Node.Fs.readFileAsUtf8Sync("inputs/input01.txt")
    -> String.split(~on="\n")
    -> List.map(~f = fuelForMassStr)
    -> List.sum

Js.log("part 1: " ++ string_of_int(part1))

// part 2

// todo: tail call optimize this with an accumulator style
let rec fuelForMassRec = (mass) => {
  let fuel = fuelForMass(mass);
  if (fuel < 0) {
    0
  } else {
    fuel + fuelForMassRec(fuel)
  }
};

let fuelForMassStrRec = (massStr) => {
  let mass = String.toInt(massStr);
  switch(mass) {
    | Ok(m) => fuelForMassRec(m)
    | Error(_) => 0
  }
};

let part2 =
  Node.Fs.readFileAsUtf8Sync("inputs/input01.txt")
    -> String.split(~on="\n")
    -> List.map(~f = fuelForMassStrRec)
    -> List.sum

Js.log("part 2, recursive: " ++ string_of_int(part2))