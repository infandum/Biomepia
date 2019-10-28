using System;
using System.Collections.Generic;
using UnityEngine;
using Object = UnityEngine.Object;

namespace Assets.Scripts.Helpers
{
    public static class Helper
    {
        public static T SafeDestroy<T>(T obj) where T : Object
        {
            if (Application.isEditor)
                Object.DestroyImmediate(obj);
            else
                Object.Destroy(obj);

            return null;
        }

        public static T SafeDestroyGameObject<T>(T component) where T : Component
        {
            if (component != null) SafeDestroy(component.gameObject);
            return null;
        }

        public static void DeactivateAllChideren(this Transform parent)
        {
            for (int i = 0; i < parent.transform.childCount; i++)
            {
                var child = parent.transform.GetChild(i).gameObject;
                if (child != null)
                    child.gameObject.SetActive(false);
            }
        }

        public static Transform[] FindChilderenWithTag(this Transform parent, string tag, bool forceActive = false)
        {
            if (parent == null) { throw new ArgumentNullException(); }
            if (String.IsNullOrEmpty(tag)) { throw new ArgumentNullException(); }
            List<Transform> list = new List<Transform>(parent.childCount);
            if (list.Count == 0) { return null; }


            for (int i = 0; i < parent.childCount; i++)
            {
                if (parent.transform.GetChild(i).CompareTag(tag))
                    list.Add(parent.transform.GetChild(i));
            }
            return list.ToArray();
        }


        public static Transform FindChildWithTag(this Transform parent, string tag, bool forceActive = false)
        {
            if (parent == null) { throw new ArgumentNullException(); }
            if (String.IsNullOrEmpty(tag)) { throw new ArgumentNullException(); }

            for (int i = 0; i < parent.childCount; i++)
            {
                if (parent.transform.GetChild(i).CompareTag(tag))
                    return parent.GetChild(i);
            }

            return null;
        }


        public static T[] FindComponentsInChildrenWithTag<T>(this GameObject parent, string tag, bool forceActive = false) where T : Component
        {
            if (parent == null) { throw new ArgumentNullException(); }
            if (String.IsNullOrEmpty(tag)) { throw new ArgumentNullException(); }
            List<T> list = new List<T>(parent.GetComponentsInChildren<T>(forceActive));
            if (list.Count == 0) { return null; }

            for (int i = list.Count - 1; i >= 0; i--)
            {
                if (list[i].CompareTag(tag) == false)
                    list.RemoveAt(i);
            }
            return list.ToArray();
        }

        public static T FindComponentInChildWithTag<T>(this GameObject parent, string tag, bool forceActive = false) where T : Component
        {
            if (parent == null) { throw new ArgumentNullException(); }
            if (String.IsNullOrEmpty(tag)) { throw new ArgumentNullException(); }

            T[] list = parent.GetComponentsInChildren<T>(forceActive);
            foreach (T t in list)
            {
                if (t.CompareTag(tag))
                    return t;
            }
            return null;
        }
    }
}
