from fastapi import FastAPI
#importing essentials
from pydantic import BaseModel

app = FastAPI()

latest_data = {"co2": 0, "timestamp": 0}

class Data(BaseModel):
    co2: float

@app.post("/update")
def update(data: Data):
    global latest_data
    from time import time
    latest_data = {"co2": data.co2, "timestamp": time()}
    return {"status": "ok"}

@app.get("/data")
def get_data():
    return latest_data
