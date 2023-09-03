using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoldPickup : MonoBehaviour
{
    public int goldvalue;
    public GameObject pickupEffect;
    

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    
    private void OnTriggerEnter(Collider other){
        if(other.tag == "Player"){

            FindObjectOfType<GameManager>().addgold(goldvalue);
            
            Instantiate(pickupEffect, transform.position, transform.rotation);
            Destroy(this.gameObject);
        }
    }
}
