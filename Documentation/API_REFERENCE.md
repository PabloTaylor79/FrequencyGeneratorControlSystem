# API Reference

## Firmware Module

### Overview
The Firmware module is responsible for the core functionality of the Frequency Generator. It provides various endpoints for controlling and configuring the generator.

### Endpoints

#### 1. Get Frequency
- **Endpoint:** `/api/firmware/get-frequency`
- **Method:** GET
- **Description:** Retrieves the current frequency set on the generator.
- **Response:** 
  ```json
  {
      "frequency": 1000,
      "unit": "Hz"
  }
  ```

#### 2. Set Frequency
- **Endpoint:** `/api/firmware/set-frequency`
- **Method:** POST
- **Description:** Sets a new frequency for the generator.
- **Request Body:** 
  ```json
  {
      "frequency": 2000,
      "unit": "Hz"
  }
  ```
- **Response:** 
  ```json
  {
      "status": "success",
      "frequency": 2000,
      "unit": "Hz"
  }
  ```

## Desktop Application Module

### Overview
The Desktop Application provides a user interface for managing the Frequency Generator. It allows users to interact with the firmware through a series of commands.

### Endpoints

#### 1. Connect to Generator
- **Endpoint:** `/api/desktop/connect`
- **Method:** POST
- **Description:** Establishes a connection to the Frequency Generator.
- **Response:** 
  ```json
  {
      "status": "connected",
      "message": "Successfully connected to the generator."
  }
  ```

#### 2. Disconnect from Generator
- **Endpoint:** `/api/desktop/disconnect`
- **Method:** POST
- **Description:** Disconnects from the Frequency Generator.
- **Response:** 
  ```json
  {
      "status": "disconnected",
      "message": "Successfully disconnected from the generator."
  }
  ```

## Conclusion
This API reference outlines the main interactions available between the firmware and the desktop application, providing developers with the information needed to effectively utilize the system.