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
  switch (n, ls) {
  | (_, []) => []
  | (0, _) => []
  | (_, [x, ...xs]) => [x, ...take(n - 1, xs)]
  };

let padTrim = (e, n, ls) => take(n, ls @ all(e));

let rec transpose = (ls) =>
  switch ls {
  | [] => []
  | [[], ..._] => []
  | ls => [List.map(List.hd, ls), ...transpose(List.map(List.tl, ls))]
  };

let shiftLeft = (board) => {
  let rec shiftHelper = (ls) =>
    switch ls {
    | [] => []
    | [0, ...rest] => shiftHelper(rest)
    | [head, 0, ...rest] => shiftHelper([head, ...rest])
    | [head, next, ...rest] when head === next => [head + next, ...shiftHelper(rest)]
    | [head, ...rest] => [head, ...shiftHelper(rest)]
    };
  List.map((ls) => padTrim(0, List.length(ls), shiftHelper(ls)), board)
};

let orient = (direction, phase, board) =>
  switch (direction, phase) {
  | (Left, _) => board
  | (Right, _) => List.map(List.rev, board)
  | (Up, _) => board |> transpose
  | (Down, Pre) => board |> List.rev |> transpose
  | (Down, Post) => board |> transpose |> List.rev
  };

let shift = (direction, board) =>
  board |> orient(direction, Pre) |> shiftLeft |> orient(direction, Post);

let unFlatten = (n, list) => {
  let rec helper = (i, acc, ls) =>
    switch (i, ls) {
    | (_, []) => [List.rev(acc)]
    | (0, _) => [List.rev(acc)] @ helper(n, [], ls)
    | (_, [h, ...t]) => helper(i - 1, [h, ...acc], t)
    };
  helper(n, [], list)
};

let randomInt = (num) => Js.Math.random() *. float_of_int(num) |> Js.Math.floor_int;

let addCell = (board) => {
  let flatBoard = List.flatten(board);
  let numZeros = List.(flatBoard |> filter((===)(0)) |> length);
  switch numZeros {
  | 0 => board
  | _ =>
    let newValue = [|2, 2, 2, 2, 4|][randomInt(5)];
    let newCellPos = randomInt(numZeros);
    let rec placeZero = (zerosFound, fb) =>
      switch (fb, zerosFound === newCellPos) {
      | ([], _) => []
      | ([0, ...t], true) => [newValue, ...placeZero(zerosFound + 1, t)]
      | ([0, ...t], false) => [0, ...placeZero(zerosFound + 1, t)]
      | ([h, ...t], _) => [h, ...placeZero(zerosFound, t)]
      };
    flatBoard |> placeZero(0) |> unFlatten(board |> List.hd |> List.length)
  }
};

let make = () =>
  [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]] |> addCell |> addCell |> addCell;

let score = (board) => List.(board |> map(fold_left((+), 0)) |> fold_left((+), 0));

let gameIsOver = (board) =>
  List.(
    [Left, Up] |> for_all((direction) => shift(direction, board) |> flatten |> for_all((!==)(0)))
  );
