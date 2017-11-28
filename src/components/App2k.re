[%bs.raw {|require('./App2k.css')|}];

type action =
  | UserEvent(GameLogic.direction)
  | AddCell
  | Restart;

type state = {
  canUpdate: bool,
  board: list(list(int)),
  score: int,
  gameOver: bool
};

let genState = (board, canUpdate) => {
  board,
  score: GameLogic.score(board),
  gameOver: GameLogic.gameIsOver(board),
  canUpdate
};

let component = ReasonReact.reducerComponent("App2k");

let make = (_children) => {
  ...component,
  initialState: () => genState(GameLogic.make(), true),
  reducer: (action, state) =>
    switch (action, state.canUpdate) {
    | (UserEvent(direction), true) =>
      ReasonReact.UpdateWithSideEffects(
        genState(GameLogic.shift(direction, state.board), false),
        ((self) => ignore(Js.Global.setTimeout(self.reduce(() => AddCell), 100)))
      )
    | (UserEvent(_), false) => ReasonReact.NoUpdate
    | (AddCell, _) => ReasonReact.Update(genState(GameLogic.addCell(state.board), true))
    | (Restart, _) => ReasonReact.Update(genState(GameLogic.make(), true))
    },
  render: ({state, reduce}) =>
    <EventLayer className="App" onAction=(reduce((direction) => UserEvent(direction)))>
      <Title score=state.score onReplay=(reduce((_event) => Restart)) />
      <div className="game-area"> <Board board=state.board /> </div>
      <Footer />
      <GameOver gameOver=state.gameOver score=state.score onReplay=(reduce((_event) => Restart)) />
    </EventLayer>
};
