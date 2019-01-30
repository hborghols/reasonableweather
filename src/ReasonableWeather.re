type optionOrError('a) =
  | Some('a)
  | None
  | Error;

type state = {
  weather: optionOrError(array(WeatherData.weather)),
  forecast: optionOrError(WeatherData.forecast),
};

type action =
  | WeatherLoaded(array(WeatherData.weather))
  | WeatherError
  | ForecastLoaded(WeatherData.forecast)
  | ForecastError;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,

  initialState: () => {weather: None, forecast: None},

  didMount: self => {
    let handleWeatherLoaded = weather => self.send(WeatherLoaded(weather));
    let handleWeatherError = () => self.send(WeatherError);
    let handleForecastLoaded = forecast =>
      self.send(ForecastLoaded(forecast));
    let handleForecastError = () => self.send(ForecastError);

    WeatherData.getWeather()
    |> Js.Promise.then_(weather => {
         handleWeatherLoaded(weather);
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(_err => {
         handleWeatherError();
         Js.Promise.resolve();
       })
    |> ignore;

    WeatherData.getForecast()
    |> Js.Promise.then_(forecast => {
         handleForecastLoaded(forecast);
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(_err => {
         handleForecastError();
         Js.Promise.resolve();
       })
    |> ignore;
    /* ReasonReact.NoUpdate; */
  },

  reducer: (action, _prevState) =>
    switch (action) {
    | WeatherLoaded(newWeather) =>
      ReasonReact.Update({..._prevState, weather: Some(newWeather)})
    | WeatherError => ReasonReact.Update({..._prevState, weather: Error})
    | ForecastLoaded(newForecast) =>
      ReasonReact.Update({..._prevState, forecast: Some(newForecast)})
    | ForecastError => ReasonReact.Update({..._prevState, forecast: Error})
    },

  render: self => {
    let weatherComponent =
      switch (self.state.weather) {
      | None => ReasonReact.string("Loading weather...")
      | Some(weather) =>
        ReasonReact.array(
          Array.map(
            (station: WeatherData.weather) =>
              switch (station.name) {
              | "Meetstation Volkel" =>
                <div
                  key={station.id}
                  style={
                    ReactDOMRe.Style.make(
                      ~display="flex",
                      ~flexDirection="column",
                      ~alignItems="center",
                      ~margin="0px 24px",
                      (),
                    )
                  }>
                  <span style={ReactDOMRe.Style.make(~fontSize="1.5em", ())}>
                    <a
                      className="buienradar-link"
                      href="https://www.buienradar.nl/weer/nijmegen/nl/2750053">
                      {ReasonReact.string("Nijmegen")}
                    </a>
                  </span>
                  <Station station />
                </div>
              | "Meetstation Groningen" =>
                <div
                  key={station.id}
                  style={
                    ReactDOMRe.Style.make(
                      ~display="flex",
                      ~flexDirection="column",
                      ~alignItems="center",
                      ~margin="0px 24px",
                      (),
                    )
                  }>
                  <span style={ReactDOMRe.Style.make(~fontSize="1.5em", ())}>
                    <a
                      className="buienradar-link"
                      href="https://www.buienradar.nl/weer/groningen/nl/2755251">
                      {ReasonReact.string("Groningen")}
                    </a>
                  </span>
                  <Station station />
                </div>
              | "Meetstation Schiphol" =>
                <div
                  key={station.id}
                  style={
                    ReactDOMRe.Style.make(
                      ~display="flex",
                      ~flexDirection="column",
                      ~alignItems="center",
                      ~margin="0px 24px",
                      (),
                    )
                  }>
                  <span style={ReactDOMRe.Style.make(~fontSize="1.5em", ())}>
                    <a
                      className="buienradar-link"
                      href="https://www.buienradar.nl/weer/amsterdam/nl/2759794">
                      {ReasonReact.string("Amsterdam")}
                    </a>
                  </span>
                  <Station station />
                </div>
              | _ => ReasonReact.string("")
              },
            weather,
          ),
        )
      | Error => ReasonReact.string("Error loading weather...")
      };
    let forecastComponent =
      switch (self.state.forecast) {
      | None => ReasonReact.string("Loading forecast...")
      | Some(forecast) => ReasonReact.string(forecast.summary)
      | Error => ReasonReact.string("Error loading forecast")
      };
    <div
      className="App"
      style={
        ReactDOMRe.Style.make(
          ~fontSize="1em",
          ~fontFamily="Helvetica",
          ~display="flex",
          ~flexDirection="column",
          ~alignItems="center",
          ~justifyContent="center",
          ~paddingTop="12em",
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
        weatherComponent
      </div>
      <div
        style={
          ReactDOMRe.Style.make(
            ~display="flex",
            ~flexDirection="row",
            ~alignItems="center",
            ~justifyContent="center",
            ~paddingTop="4em",
            ~maxWidth="600px",
            ~fontSize="1.5em",
            (),
          )
        }>
        forecastComponent
      </div>
      <p
        style={
          ReactDOMRe.Style.make(
            ~bottom="0px",
            ~right="0px",
            ~position="absolute",
            (),
          )
        }>
        {ReasonReact.string("data van: ")}
        <a className="buienradar-link" href="https://www.buienradar.nl">
          {ReasonReact.string("https://www.buienradar.nl")}
        </a>
      </p>
    </div>;
  },
};