using UnityEditor;
using UnityEngine;

namespace Assets.Editor.HexGenerator
{
    [CustomEditor(typeof(Scripts.HexGenerator.HexGenerator))]
    public class HexGeneratorEditor : UnityEditor.Editor
    {
        public override void OnInspectorGUI()
        {
            //DrawDefaultInspector();
            Scripts.HexGenerator.HexGenerator hexGenerator = (Scripts.HexGenerator.HexGenerator) target;
            hexGenerator.HeightMap = (Texture2D)EditorGUILayout.ObjectField("Height map:", hexGenerator.HeightMap, typeof(Texture2D), true);
            hexGenerator.HeightMultiplier = EditorGUILayout.FloatField("Height Multiplier:", hexGenerator.HeightMultiplier);
            hexGenerator.HeightGrowth = EditorGUILayout.FloatField("Height Growth:", hexGenerator.HeightGrowth);

            EditorGUILayout.Separator();

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

            EditorGUILayout.Separator();

            
            hexGenerator.IsOnlyInsideCollider = EditorGUILayout.Toggle("Inside Collider Only:", hexGenerator.IsOnlyInsideCollider);
            EditorGUILayout.LabelField("Currently ONLY supports Box or Sphere colliders", EditorStyles.boldLabel);

            EditorGUILayout.Separator();
            if (GUILayout.Button("Build map"))
            {
                hexGenerator.GenerateMap();
            }
        }
    }
}
