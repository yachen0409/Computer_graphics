using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class test : MonoBehaviour
{
    public bool onPlain = false;
    public int a = 0;
    public Collider movingplain;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(onPlain){
            transform.parent = movingplain.transform;
        }
        else{
            transform.parent = null;
        }
        
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.transform.tag == "Moving")
        {
            a++;
            onPlain = true;
            movingplain=other;
            transform.parent = other.transform;
            //Debug.Log("We are on a moving platform");
        }
    }
 
    private void OnTriggerExit(Collider other)
    {
        if (other.transform.tag == "Moving")
        {
            a--;
            onPlain = false;
            transform.parent = null;
        }
    }
}
