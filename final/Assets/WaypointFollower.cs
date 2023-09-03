using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaypointFollower : MonoBehaviour
{
    public GameObject[] waypoints;
    public int currentWaypointIndex = 0;
    public Vector3 movedir;
    public Vector3 movingmove;
    public float speed = 3f;
    private float characterspeed = 6f;
    // Start is called before the first frame update
    void Start()
    {
        movedir = waypoints[currentWaypointIndex].transform.position - transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if(Vector3.Distance(transform.position, waypoints[currentWaypointIndex].transform.position) < .1f){
            currentWaypointIndex++;
            if(currentWaypointIndex >= waypoints.Length){
                currentWaypointIndex = 0;
            }
            movedir = waypoints[currentWaypointIndex].transform.position - transform.position;
        }
        transform.position = Vector3.MoveTowards(transform.position, waypoints[currentWaypointIndex].transform.position, speed * Time.deltaTime);
        movingmove = (movedir * speed * Time.deltaTime * characterspeed);
        

        

    }
    public Vector3 getplainmove(){
        
        return movingmove;
    }
}
