type boardType = list(list(int));

type direction =
  | Left
  | Right
  | Up
  | Down;

type orientPhase =
  | Pre
  | Post;

let all = (x) => {
  let rec xs = [x, ...xs];
  xs
};

let rec take = (n, ls) =>
  switch ls {
  | [] => []
  | _ when n === 0 => []
  | [x, ...xs] => [x, ...take(n - 1, xs)]
  };

let padTrim = (e, n, ls) => take(n, ls @ all(e));

let rec transpose = (ls) =>
  switch ls {
  | [] => []
  | [[], ..._] => []
  | ls => [List.map(List.hd, ls), ...transpose(List.map(List.tl, ls))]
  };

let transformLeft = (board) => {
  let rec transformHelper = (ls) =>
    switch ls {
    | [] => []
    | [0, ...rest] => transformHelper(rest)
    | [head, 0, ...rest] => transformHelper([head, ...rest])
    | [head, next, ...rest] when head === next => [head + next, ...transformHelper(rest)]
    | [head, ...rest] => [head, ...transformHelper(rest)]
    };
  List.map((ls) => padTrim(0, List.length(ls), transformHelper(ls)), board)
};

let orient = (direction, phase, board) =>
  switch (direction, phase) {
  | (Left, _) => board
  | (Right, _) => List.map(List.rev, board)
  | (Up, _) => board |> transpose
  | (Down, Pre) => board |> List.rev |> transpose
  | (Down, Post) => board |> transpose |> List.rev
  };

let transform = (direction, board) =>
  board |> orient(direction, Pre) |> transformLeft |> orient(direction, Post);

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

let score = (board) => List.(board |> map(fold_left((+), 0)) |> fold_left((+), 0));

let gameIsOver = (board) =>
  List.(
    [Left, Up]
    |> for_all((direction) => transform(direction, board) |> flatten |> for_all((!==)(0)))
  );