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
                <p key={station.id}>
                  <a
                    className="buienradar-link"
                    href="https://www.buienradar.nl/weer/nijmegen/nl/2750053">
                    {ReasonReact.string("Nijmegen")}
                  </a>
                  {ReasonReact.string("/")}
                  <a
                    className="buienradar-link"
                    href="https://www.buienradar.nl/weer/oss/nl/2749234">
                    {ReasonReact.string("Oss")}
                  </a>
                  {
                    ReasonReact.string(
                      ": "
                      ++ (
                        switch (station.temp) {
                        | Some(temp) => string_of_float(temp) ++ "C"
                        | None => "No temp found"
                        }
                      )
                      ++ ", "
                      ++ station.summary
                      ++ " ",
                    )
                  }
                </p>
              | "Meetstation Groningen" =>
                <p key={station.id}>
                  <a
                    className="buienradar-link"
                    href="https://www.buienradar.nl/weer/groningen/nl/2755251">
                    {ReasonReact.string("Groningen")}
                  </a>
                  {
                    ReasonReact.string(
                      ": "
                      ++ (
                        switch (station.temp) {
                        | Some(temp) => string_of_float(temp) ++ "C"
                        | None => "No temp found"
                        }
                      )
                      ++ ", "
                      ++ station.summary
                      ++ " ",
                    )
                  }
                </p>
              | "Meetstation Schiphol" =>
                <p key={station.id}>
                  <a
                    className="buienradar-link"
                    href="https://www.buienradar.nl/weer/amsterdam/nl/2759794">
                    {ReasonReact.string("Amsterdam")}
                  </a>
                  {
                    ReasonReact.string(
                      ": "
                      ++ (
                        switch (station.temp) {
                        | Some(temp) => string_of_float(temp) ++ "C"
                        | None => "No temp found"
                        }
                      )
                      ++ ", "
                      ++ station.summary
                      ++ " ",
                    )
                  }
                </p>
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
    <div className="App">
      <h1> {ReasonReact.string("Huidig weer:")} </h1>
      <p> weatherComponent </p>
      <h1> {ReasonReact.string("Voorspelling: ")} </h1>
      <p> forecastComponent </p>
      <p>
        {ReasonReact.string("data van: ")}
        <a className="buienradar-link" href="https://www.buienradar.nl">
          {ReasonReact.string("https://www.buienradar.nl")}
        </a>
      </p>
    </div>;
  },
};