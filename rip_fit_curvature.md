#!/usr/bin/env python3

print("Hello, World!")

import numpy as np

# Generate synthetic data
np.random.seed(42)
latitudes = np.random.uniform(-90, 90, 1000)
longitudes = np.random.uniform(-180, 180, 1000)

# Approximate curvature (simplified for demonstration: curvature decreases with distance from the equator)
curvature = 1 / (1 + np.abs(latitudes) / 90)

# Stack the coordinates and curvature
data = np.column_stack((latitudes, longitudes, curvature))

# Split the data into training and testing sets
train_data = data[:800]
test_data = data[800:]

X_train = train_data[:, :2]
y_train = train_data[:, 2]
X_test = test_data[:, :2]
y_test = test_data[:, 2]

#!pip install tensorflow

import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# Define the model
model = Sequential([
    Dense(64, activation='relu', input_shape=(2,)),
    Dense(64, activation='relu'),
    Dense(1)  # Output layer for predicting curvature
])

# Compile the model
model.compile(optimizer='adam', loss='mean_squared_error')

# Print the model summary
model.summary()

# Train the model
history = model.fit(X_train, y_train, epochs=50, batch_size=32, validation_split=0.2)

# Evaluate the model
test_loss = model.evaluate(X_test, y_test)
print(f'Test loss: {test_loss}')

# Predict curvature for the test set
y_pred = model.predict(X_test)

# Print some predictions
for i in range(5):
    print(f'Latitude: {X_test[i, 0]}, Longitude: {X_test[i, 1]}, Actual Curvature: {y_test[i]}, Predicted Curvature: {y_pred[i][0]}')
