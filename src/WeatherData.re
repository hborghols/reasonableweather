type weather = {
  name: string,
  summary: string,
  temp: option(float),
  id: string,
  imageUrl: string,
};

type forecast = {summary: string};

let url = "https://api.buienradar.nl/data/public/2.0/jsonfeed";

let parseWeatherJson = json =>
  Json.Decode.{
    name: field("stationname", string, json),
    summary: field("weatherdescription", string, json),
    temp: field("temperature", optional(Json.Decode.float), json),
    id: string_of_int(field("stationid", int, json)),
    imageUrl: field("iconurl", string, json),
  };

let parseWeatherStationsJson = json =>
  Json.Decode.array(parseWeatherJson, json);

let parseWeatherResultsJson = json =>
  Json.parseOrRaise(json)
  |> Json.Decode.at(
       ["actual", "stationmeasurements"],
       parseWeatherStationsJson,
     );

let getWeather = () =>
  Js.Promise.(
    Bs_fetch.fetch(url)
    |> then_(Bs_fetch.Response.text)
    |> then_(jsonText =>
         switch (parseWeatherResultsJson(jsonText)) {
         | exception e => reject(e)
         | weather => resolve(weather)
         }
       )
  );

let parseForecastJson = json: forecast =>
  Json.Decode.{summary: field("summary", string, json)};

let parseForecastResultJson = json =>
  Json.parseOrRaise(json)
  |> Json.Decode.at(["forecast", "weatherreport"], parseForecastJson);

let getForecast = () =>
  Js.Promise.(
    Bs_fetch.fetch(url)
    |> then_(Bs_fetch.Response.text)
    |> then_(jsonText =>
         switch (parseForecastResultJson(jsonText)) {
         | exception e => reject(e)
         | forecast => resolve(forecast)
         }
       )
  );