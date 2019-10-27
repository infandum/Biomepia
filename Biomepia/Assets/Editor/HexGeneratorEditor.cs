using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;


[CustomEditor(typeof(HexGenerator))]
public class HexGeneratorEditor : Editor
{
    //AnimationCurve curveX = AnimationCurve.Linear(0, 0, 10, 10);
    //AnimationCurve curveY = AnimationCurve.Linear(0, 0, 10, 10);
    //AnimationCurve curveZ = AnimationCurve.Linear(0, 0, 10, 10);


    public override void OnInspectorGUI()
    {
        //DrawDefaultInspector();
        HexGenerator hexGenerator = (HexGenerator) target;
        hexGenerator.HeightMap = (Texture2D)EditorGUILayout.ObjectField("Height map:", hexGenerator.HeightMap, typeof(Texture2D), true);
        hexGenerator.HeightMultiplier = EditorGUILayout.FloatField("Height Multiplier:", hexGenerator.HeightMultiplier);
        hexGenerator.HeightGrowth = EditorGUILayout.FloatField("Height Growth:", hexGenerator.HeightGrowth);

        hexGenerator.IsGenerateRect = EditorGUILayout.Toggle("Generate Rect:", hexGenerator.IsGenerateRect);

        if (hexGenerator.IsGenerateRect)
        {
            hexGenerator.RectSize = EditorGUILayout.Vector2IntField("Rectangle Size:", hexGenerator.RectSize);
            if (GUILayout.Button("Force To Square"))
            {
                hexGenerator.RectSize.y = Mathf.RoundToInt((hexGenerator.RectSize.x * 1.15f));
            }
        }
        else
        {
            hexGenerator.HexRadius = EditorGUILayout.IntField("Rectangle Size:", hexGenerator.HexRadius);
        }


        hexGenerator.IsOnlyInsideCollidor = EditorGUILayout.Toggle("Inside Collider Only:", hexGenerator.IsOnlyInsideCollidor);

        if (GUILayout.Button("Build map"))
        {
            hexGenerator.GenerateMap();
        }

        //curveX = EditorGUILayout.CurveField("Animation on X", curveX);
        //curveY = EditorGUILayout.CurveField("Animation on Y", curveY);
        //curveZ = EditorGUILayout.CurveField("Animation on Z", curveZ);
    }
}
