from fastapi import FastAPI
from datetime import datetime

app = FastAPI()
latest = {
    "value": None,
    "timestamp": None
}
history = []

@app.post("/update")
async def update(data: dict):
    global latest, history
    latest = {
        "value": data["value"],
        "timestamp": datetime.utcnow().isoformat()
    }
    history.append(latest)
    if len(history) > 1000:  
        history = history[-1000:]
    return {"ok": True}

@app.get("/latest")
async def get_latest():
    return latest

@app.get("/history")
async def get_history():
    return history
