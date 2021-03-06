type boardType = list(list(int));

type direction =
  | Left
  | Right
  | Up
  | Down;

let shift: (direction, boardType) => boardType;

let addCell: boardType => boardType;

let make: unit => boardType;

let score: boardType => int;

let gameIsOver: boardType => bool;
