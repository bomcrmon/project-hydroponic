import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';
import { environment } from 'src/environments/environment';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit{
  humidityValue: any;
  temperatureValue:any
  pHValue:any
  fertilizersState:any
  waterState:any
  fan:any
  led:any
  pump_ph_down:any
  pump_ph_up:any
  pump_water_up:any
  sprinklerfertilizers:any
  sprinklerwater:any
  constructor(private auth:AuthService) {
    
  }

  ngOnInit(): void {
    this.auth.humidityValue().subscribe((value: any) => {
      this.humidityValue = value;
    });
    this.auth.temperatureValue().subscribe((value: any) => {
      this.temperatureValue = value;
    });
    this.auth.pHValue().subscribe((value: any) => {
      this.pHValue = value;
    });
    this.auth.fertilizersState().subscribe((state: any) => {
      this.fertilizersState = state;
    });
    this.auth.waterState().subscribe((state: any) => {
      this.waterState = state;
    });
    this.auth.fan().subscribe((state: any) => {
      this.fan = state;
    });
    this.auth.led().subscribe((state: any) => {
      this.led = state;
    });
    this.auth.pump_ph_down().subscribe((state: any) => {
      this.pump_ph_down = state;
    });
    this.auth.pump_ph_up().subscribe((state: any) => {
      this.pump_ph_up = state;
    });
    this.auth.pump_water_up().subscribe((state: any) => {
      this.pump_water_up = state;
    });
    this.auth.sprinklerfertilizers().subscribe((state: any) => {
      this.sprinklerfertilizers = state;
    });
    this.auth.sprinklerwater().subscribe((state: any) => {
      this.sprinklerwater = state;
    });

    
  }


  logout(){
  this.auth.logout();
  }


}
