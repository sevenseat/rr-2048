type boardType = list(list(int));

type direction =
  | Left
  | Right
  | Up
  | Down;

type orientPhase =
  | PreTransform
  | PostTransform;

let rec transpose = (ls) =>
  switch ls {
  | [] => []
  | [[], ..._] => []
  | ls => [List.map(List.hd, ls), ...transpose(List.map(List.tl, ls))]
  };

let transform = (direction, board) => {
  let transformList = (cells) => {
    let rec transformHelper = (cells) =>
      switch cells {
      | [] => []
      | [0, ...rest] => transformHelper(rest)
      | [head, 0, ...rest] => transformHelper([head, ...rest])
      | [head, next, ...rest] when head === next => [head + next, ...transformHelper(rest)]
      | [head, ...rest] => [head, ...transformHelper(rest)]
      };
    let rec padRight = (minLength, padEntry, list) =>
      switch (minLength <= 0, list) {
      | (true, _) => list
      | (false, []) => [padEntry, ...padRight(minLength - 1, padEntry, [])]
      | (false, [head, ...rest]) => [head, ...padRight(minLength - 1, padEntry, rest)]
      };
    cells |> transformHelper |> padRight(List.length(cells), 0)
  };
  let orientBoard = (direction, phase, board) =>
    switch (direction, phase) {
    | (Left, _) => board
    | (Right, _) => List.map(List.rev, board)
    | (Up, _) => board |> transpose
    | (Down, PreTransform) => board |> List.rev |> transpose
    | (Down, PostTransform) => board |> transpose |> List.rev
    };
  board
  |> orientBoard(direction, PreTransform)
  |> List.map(transformList)
  |> orientBoard(direction, PostTransform)
};

let randomInt = (num) => Js.Math.random() *. float_of_int(num) |> Js.Math.floor_int;

let addCell = (board) => {
  let numZeros = List.(board |> flatten |> filter((===)(0)) |> length);
  let newCellPos = randomInt(numZeros);
  let newCellVal = [|2, 2, 2, 2, 4|][randomInt(5)];
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

let make = () =>
  [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]] |> addCell |> addCell |> addCell;

let score = (board) => board |> List.map(List.fold_left((+), 0)) |> List.fold_left((+), 0);

let gameIsOver = (board) =>
  List.(
    [Left, Up]
    |> exists((direction) => transform(direction, board) |> flatten |> exists((===)(0)))
    |> (!)
  );