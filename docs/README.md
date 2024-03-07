# Docs

This document page will be overwritten with formal API docs.

## Firmware API

### `/`

Displays a simple web page with a GET request.

### "/settings"

Updates the settings with a simple SCHEMA

### "/status"

Returns a JSON object:

```json
{
  "moisture": "float",
  "free_heap": "uint32_t"
}
```
