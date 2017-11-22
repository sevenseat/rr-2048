type direction =
  | Left
  | Right
  | Up
  | Down;

let rec padRight = (minLength, padEntry, list) =>
  switch (minLength <= 0, list) {
  | (true, _) => list
  | (false, []) => [padEntry, ...padRight(minLength - 1, padEntry, [])]
  | (false, [head, ...rest]) => [head, ...padRight(minLength - 1, padEntry, rest)]
  };

let rec transformHelper = (cells) =>
  switch cells {
  | [] => []
  | [0, ...rest] => transformHelper(rest)
  | [head, 0, ...rest] => transformHelper([head, ...rest])
  | [head, next, ...rest] when head === next => [head + next, ...transformHelper(rest)]
  | [head, ...rest] => [head, ...transformHelper(rest)]
  };

let transformList = (cells) => cells |> transformHelper |> padRight(List.length(cells), 0);

let rec transpose = (board) =>
  switch board {
  | [] => []
  | [[], ...xss] => transpose(xss)
  | [[x, ...xs], ...xss] => [
      [x, ...List.map(List.hd, xss)],
      ...transpose([xs, ...List.map(List.tl, xss)])
    ]
  };

type orientPhase =
  | PreTransform
  | PostTransform;

let orientBoard = (direction, phase, board) =>
  switch (direction, phase) {
  | (Left, _) => board
  | (Right, _) => List.map(List.rev, board)
  | (Up, _) => board |> transpose
  | (Down, PreTransform) => board |> List.rev |> transpose
  | (Down, PostTransform) => board |> transpose |> List.rev
  };

let transformBoard = (direction, board) =>
  board
  |> orientBoard(direction, PreTransform)
  |> List.map(transformList)
  |> orientBoard(direction, PostTransform);

let addCellHelper = (newCellPos, newCellVal, board) => {
  let procRow = (row, startZeros) =>
    row
    |> List.fold_left(
         ((cells, zerosFound), cell) =>
           switch (cell, zerosFound) {
           | (0, z) when z === newCellPos => ([newCellVal, ...cells], zerosFound + 1)
           | (0, _) => ([0, ...cells], zerosFound + 1)
           | (cell, _) => ([cell, ...cells], zerosFound)
           },
         ([], startZeros)
       )
    |> (((rows, zeros)) => (List.rev(rows), zeros));
  board
  |> List.fold_left(
       ((rows, zerosFound), row) => {
         let (resRow, resZeros) = procRow(row, zerosFound);
         ([resRow, ...rows], resZeros)
       },
       ([], 0)
     )
  |> (((b, _)) => List.rev(b))
};

let addCell = (board) => {
  Random.init([%bs.raw {|Math.random() * 10000|}]);
  let numZeros = List.(board |> flatten |> filter((cell) => cell === 0) |> length);
  let newCellPos = Random.int(numZeros);
  let newCellVal = [|2, 2, 2, 2, 4|][Random.int(5)];
  addCellHelper(newCellPos, newCellVal, board)
};

let scoreBoard = (board) => board |> List.map(List.fold_left((+), 0)) |> List.fold_left((+), 0);
