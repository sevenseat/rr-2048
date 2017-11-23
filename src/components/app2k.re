[%bs.raw {|require('./app2k.css')|}];

type action =
  | UserEvent(GameLogic.direction)
  | Restart
  | None;

type state = {
  board: list(list(int)),
  score: int
};

let component = ReasonReact.reducerComponent("App2k");

let make = (_children) => {
  let keyDown = (event) =>
    switch (ReactEventRe.Keyboard.which(event)) {
    | 37 => UserEvent(GameLogic.Left)
    | 38 => UserEvent(GameLogic.Up)
    | 39 => UserEvent(GameLogic.Right)
    | 40 => UserEvent(GameLogic.Down)
    | _ => None
    };
  let genState = (board) => {board, score: GameLogic.scoreBoard(board)};
  {
    ...component,
    initialState: () => genState(GameLogic.makeBoard()),
    reducer: (action, state) =>
      switch action {
      | UserEvent(direction) =>
        ReasonReact.Update(
          genState(GameLogic.transformBoard(direction, state.board) |> GameLogic.addCell)
        )
      | Restart => ReasonReact.Update(genState(GameLogic.makeBoard()))
      | None => ReasonReact.NoUpdate
      },
    render: ({state, reduce}) =>
      <div className="App" onKeyDown=(reduce(keyDown)) tabIndex=0>
        <Title score=state.score onReplay=(reduce((_event) => Restart)) />
        <div className="game-area"> <Board board=state.board /> </div>
      </div>
  }
};
