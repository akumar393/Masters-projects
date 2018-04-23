# Tutorial to plot us map from: https://cran.r-project.org/web/packages/googleVis/vignettes/googleVis_examples.html

# Part 3

# Ravi Malik
# Abhinav Kumar


install.packages("ggmap", "maptools", "maps", "RJSONIO", "plyr", "jsonlite", "googleVis")

library("ggmap")
library("maptools")
library("maps")
library("RJSONIO")
library("plyr")
library("jsonlite")
library("googleVis")

d <- fromJSON("data_cleaned.json", simplifyVector = TRUE)

final_data <- count(d, "state")
final_data <- final_data[-1,]

require(datasets)

states <- data.frame(state.name, state.x77)
GeoStates <- gvisGeoChart(final_data, "state", "freq",
                          options=list(region="US", 
                                       displayMode="regions", 
                                       resolution="provinces",
                                       width=600, height=400))
plot(GeoStates)
