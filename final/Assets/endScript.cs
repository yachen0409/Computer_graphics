using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class endScript : MonoBehaviour
{
    // Start is called before the first frame update
    public AudioSource ggsound;
    public AudioSource gg2sound;
    void Start()
    { 
         ggsound.Play();
         gg2sound.Play();
         Cursor.lockState = CursorLockMode.None;
    }

    // Update is called once per frame
    void Update()
    {
         Cursor.lockState = CursorLockMode.None;
    }
}
