/* This is the basic component. */
let component = ReasonReact.statelessComponent("WeatherStation");

let make = (~station: WeatherData.weather, _children) => {
  ...component,
  render: _self =>
    <div
      style={
        ReactDOMRe.Style.make(
          ~display="flex",
          ~flexDirection="column",
          ~alignItems="center",
          (),
        )
      }>
      <div
        style={
          ReactDOMRe.Style.make(
            ~display="flex",
            ~flexDirection="row",
            ~alignItems="center",
            (),
          )
        }>
        <span style={ReactDOMRe.Style.make(~fontSize="48px", ())}>
          {
            ReasonReact.string(
              switch (station.temp) {
              | Some(temp) => string_of_float(temp)
              | None => "No temp found"
              },
            )
          }
        </span>
        <span
          style={
            ReactDOMRe.Style.make(
              ~fontSize="24px",
              ~marginTop="6px",
              ~alignSelf="flex-start",
              (),
            )
          }>
          {ReasonReact.string("\xB0C")}
        </span>
        <img src={station.imageUrl} />
      </div>
      <span> {ReasonReact.string(station.summary)} </span>
    </div>,
};