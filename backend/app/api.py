from fastapi import APIRouter, UploadFile, File, HTTPException
from fastapi.responses import FileResponse
import os
import subprocess
import shutil
from pathlib import Path

router = APIRouter()

@router.post("/detect")
async def detect(file: UploadFile = File(...)):
    try:
        uploads_dir = Path("cpp/dataset")
        uploads_dir.mkdir(parents=True, exist_ok=True)

        results_dir = Path("cpp/results")
        results_dir.mkdir(parents=True, exist_ok=True)

        img_path = uploads_dir / file.filename
        with open(img_path, "wb") as f:
            f.write(await file.read())

        build_detector = Path("build/cpp/face_detector")
        if not build_detector.exists():
            raise HTTPException(status_code=500, detail="Detector is not built")

        result = subprocess.run(
            [str(build_detector), str(img_path)],
            capture_output=True,
            text=True
        )

        if result.returncode != 0:
            raise HTTPException(status_code=500, detail=f"Detector failed: {result.stderr}")
        
        output_image = results_dir / f"{img_path.stem}_detected.jpg"
        if not output_image.exists():
            raise HTTPException(
                status_code=500,
                detail=f"Output image is not created.\nstdout:\n{result.stdout}\nstderr:\n{result.stderr}"
            )

        return {
            "status": "success",
            "input": str(img_path),
            "output": str(output_image),
            "stdout": result.stdout
        }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
    
@router.get("/results/{filename}")
async def get_results(filename: str):
    result_path = Path("cpp/results") / filename
    if not result_path.exists():
        raise HTTPException(status_code=404, detail="Result of detection is not found")
    return FileResponse(result_path)